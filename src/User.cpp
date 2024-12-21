#include "User.h"
#include <iostream>

std::unordered_map<std::string, std::string> userCredentials;

User::User(int id, const std::string& name, const std::string& password)
    : userID(id), name(name), password(password), latitude(0), longitude(0) {}

void User::registerUser() {
    userCredentials[name] = password;
    std::cout << "User registered successfully!" << std::endl;
}

void User::login() {
    std::string inputName, inputPassword;
    std::cout << "Enter name: ";
    std::cin >> inputName;
    std::cout << "Enter password: ";
    std::cin >> inputPassword;

    if (userCredentials.find(inputName) != userCredentials.end() && userCredentials[inputName] == inputPassword) {
        std::cout << "Login successful!" << std::endl;
    } else {
        std::cout << "Invalid credentials!" << std::endl;
    }
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