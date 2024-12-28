#include "User.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

int User::userCount = 0;

User::User() : latitude(0), longitude(0) {}

User::User(const std::string& name, const std::string& phoneNumber, const std::string& password)
    : name(name), phoneNumber(phoneNumber), password(password), latitude(0), longitude(0) {
    userID = generateUserID(name, phoneNumber);
}

void User::registerUser() {
    // Save user data to a file or database
    saveUserData();
    cout << "User registered successfully. Your userID is: " << userID << endl;
}

bool User::login(const std::string& userID, const std::string& password) {
    User user;
    if (loadUserData(userID, user) && user.password == password) {
        *this = user;
        return true;
    }
    cout << "Invalid userID or password." << endl;
    return false;
}

void User::addRideToHistory(int rideID, const std::string& status, const Location& pickup, const Location& destination, const std::string& driver) {
    rideHistory.push_back(make_tuple(rideID, status, pickup, destination, driver));
    updateUserData(*this);
}

std::vector<std::tuple<int, std::string, Location, Location, std::string>> User::getRideHistory() const {
    return rideHistory;
}

void User::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
    updateUserData(*this);
}

std::pair<double, double> User::getLocation() const {
    return {latitude, longitude};
}

std::string User::generateUserID(const std::string& name, const std::string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.size() - 2) + to_string(userCount++);
}

void User::saveUserData() const {
    ofstream file("userdata.txt", ios::app);
    if (!file) {
        throw runtime_error("Unable to save user data.");
    }
    file << userID << " " << name << " " << phoneNumber << " " << password << " " << latitude << " " << longitude << endl;
    file.close();
}

bool User::loadUserData(const std::string& userID, User& user) {
    ifstream file("userdata.txt");
    if (!file) {
        return false;
    }
    string id, name, phone, pass;
    double lat, lon;
    while (file >> id >> name >> phone >> pass >> lat >> lon) {
        if (id == userID) {
            user.userID = id;
            user.name = name;
            user.phoneNumber = phone;
            user.password = pass;
            user.latitude = lat;
            user.longitude = lon;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void User::updateUserData(const User& user) {
    ifstream file("userdata.txt");
    ofstream tempFile("temp.txt");
    if (!file || !tempFile) {
        throw runtime_error("Unable to update user data.");
    }
    string id, name, phone, pass;
    double lat, lon;
    while (file >> id >> name >> phone >> pass >> lat >> lon) {
        if (id == user.userID) {
            tempFile << user.userID << " " << user.name << " " << user.phoneNumber << " " << user.password << " " << user.latitude << " " << user.longitude << endl;
        } else {
            tempFile << id << " " << name << " " << phone << " " << pass << " " << lat << " " << lon << endl;
        }
    }
    file.close();
    tempFile.close();
    remove("userdata.txt");
    rename("temp.txt", "userdata.txt");
}

void User::viewProfile() const {
    cout << "\n ૮₍˶ᵔᵕᵔ˶₎ა User Profile:" << endl;
    cout << " — User ID: " << userID << endl;
    cout << " — Name: " << name << endl;
    cout << " — Phone Number: " << phoneNumber << endl;
    cout << " — Current Location: (" << latitude << ", " << longitude << ")" << endl;
    cout << "\n ˚ ༘`✦ ˑ ִֶ 𓂃⊹ Ride History: " << endl;
    for (const auto& ride : rideHistory) {
        cout << " → Ride ID: " << get<0>(ride) << ",\n — Status: " << get<1>(ride) 
             << ",\n — Pickup: " << get<2>(ride).getName() << ",\n — Destination: " << get<3>(ride).getName()
             << ",\n — Driver: " << get<4>(ride) << endl;
    }
}