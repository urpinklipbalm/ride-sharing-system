#include "User.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>

using namespace std;

// Placeholder for ride requests
queue<pair<string, pair<double, double>>> rideRequests; // Pair of user ID and destination coordinates

User::User(const string& name, const string& phoneNumber, const string& password)
    : name(name), phoneNumber(phoneNumber), password(password), latitude(0.0), longitude(0.0) {
    userID = generateUserID(name, phoneNumber);
}

void User::registerUser() {
    ofstream userDataFile("userdata.txt", ios::app);
    if (userDataFile.is_open()) {
        userDataFile << userID << " " << name << " " << phoneNumber << " " << password << endl;
        userDataFile.close();
        cout << "User registered successfully! Your userID is: " << userID << endl;
    } else {
        cout << "Unable to open file for writing user data." << endl;
    }
}

bool User::login(const string& inputUserID, const string& inputPassword) {
    ifstream userDataFile("userdata.txt");
    string fileUserID, fileName, filePhoneNumber, filePassword;
    if (userDataFile.is_open()) {
        while (userDataFile >> fileUserID >> fileName >> filePhoneNumber >> filePassword) {
            if (fileUserID == inputUserID && filePassword == inputPassword) {
                userID = fileUserID;
                name = fileName;
                phoneNumber = filePhoneNumber;
                password = filePassword;
                userDataFile.close();
                cout << "Login successful!" << endl;
                return true;
            }
        }
        userDataFile.close();
    } else {
        cout << "Unable to open file for reading user data." << endl;
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