#include "User.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

User::User() {}

User::User(const std::string& name, const std::string& phoneNumber, const std::string& password)
    : name(name), phoneNumber(phoneNumber), password(password) {
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

void User::requestRide(double destinationLatitude, double destinationLongitude) {
    // Implementation for requesting a ride
}

void User::addRideToHistory(int rideID, const std::string& status) {
    rideHistory.push_back({rideID, status});
}

std::vector<std::pair<int, std::string>> User::getRideHistory() const {
    return rideHistory;
}

void User::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

std::pair<double, double> User::getLocation() const {
    return {latitude, longitude};
}

std::string User::generateUserID(const std::string& name, const std::string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.size() - 2) + to_string(rand() % 1000);
}

void User::saveUserData() const {
    ofstream file("userdata.txt", ios::app);
    if (!file) {
        throw runtime_error("Unable to save user data.");
    }
    file << userID << " " << name << " " << phoneNumber << " " << password << endl;
    file.close();
}

bool User::loadUserData(const std::string& userID, User& user) {
    ifstream file("userdata.txt");
    if (!file) {
        return false;
    }
    string id, name, phone, pass;
    while (file >> id >> name >> phone >> pass) {
        if (id == userID) {
            user.userID = id;
            user.name = name;
            user.phoneNumber = phone;
            user.password = pass;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}