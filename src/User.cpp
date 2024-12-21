#include "User.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

// Placeholder for ride requests
queue<pair<string, pair<double, double>>> rideRequests; // Pair of user ID and destination coordinates

User::User() : latitude(0.0), longitude(0.0) {}

User::User(const string& name, const string& phoneNumber, const string& password)
    : name(name), phoneNumber(phoneNumber), password(password), latitude(0.0), longitude(0.0) {
    if (phoneNumber.length() >= 3) {
        userID = generateUserID(name, phoneNumber);
    } else {
        throw out_of_range("Phone number is too short to generate userID");
    }
}

void User::registerUser() {
    saveUserData();
    cout << "User registered successfully! Your userID is: " << userID << endl;
}

bool User::login(const string& inputUserID, const string& inputPassword) {
    if (loadUserData(inputUserID, *this) && password == inputPassword) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid userID or password." << endl;
    return false;
}

void User::requestRide(double destinationLatitude, double destinationLongitude) {
    rideRequests.push({userID, {destinationLatitude, destinationLongitude}});
    cout << "Ride requested by user " << name << " to (" << destinationLatitude << ", " << destinationLongitude << ")" << endl;
}

void User::addRideToHistory(int rideID, const string& status) {
    rideHistory.push_back({rideID, status});
}

vector<pair<int, string>> User::getRideHistory() const {
    return rideHistory;
}

void User::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
    cout << "User " << name << " location updated to (" << latitude << ", " << longitude << ")" << endl;
}

pair<double, double> User::getLocation() const {
    return make_pair(latitude, longitude);
}

string User::generateUserID(const string& name, const string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.length() - 3);
}

void User::saveUserData() const {
    ofstream userDataFile("userdata.txt", ios::app);
    if (userDataFile.is_open()) {
        userDataFile << userID << " " << name << " " << phoneNumber << " " << password << endl;
        userDataFile.close();
    } else {
        cout << "Unable to open file for writing user data." << endl;
    }
}

bool User::loadUserData(const string& inputUserID, User& user) {
    ifstream userDataFile("userdata.txt");
    string fileUserID, fileName, filePhoneNumber, filePassword;
    if (userDataFile.is_open()) {
        while (userDataFile >> fileUserID >> fileName >> filePhoneNumber >> filePassword) {
            if (fileUserID == inputUserID) {
                user.userID = fileUserID;
                user.name = fileName;
                user.phoneNumber = filePhoneNumber;
                user.password = filePassword;
                userDataFile.close();
                return true;
            }
        }
        userDataFile.close();
    } else {
        cout << "Unable to open file for reading user data." << endl;
    }
    return false;
}