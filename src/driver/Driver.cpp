#include "Driver.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <cmath>

using namespace std;

Driver::Driver() : available(false) {}

Driver::Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm)
    : name(name), password(password), vehicleRegistration(vehicleRegistration), phoneNumber(phoneNumber), ratePerKm(ratePerKm), available(false) {
    driverID = generateDriverID(name, phoneNumber);
}

void Driver::registerDriver() {
    // Save driver data to a file or database
    saveDriverData();
    cout << "Driver registered successfully. Your driverID is: " << driverID << endl;
}

bool Driver::login(const std::string& driverID, const std::string& password) {
    Driver driver;
    if (loadDriverData(driverID, driver) && driver.password == password) {
        *this = driver;
        return true;
    }
    cout << "Invalid driverID or password." << endl;
    return false;
}

void Driver::setAvailability(bool availability) {
    available = availability;
}

bool Driver::isAvailable() const {
    return available;
}

void Driver::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

std::pair<double, double> Driver::getLocation() const {
    return {latitude, longitude};
}

void Driver::addRideToHistory(int rideID, const std::string& status) {
    rideHistory.push_back({rideID, status});
}

std::vector<std::pair<int, std::string>> Driver::getRideHistory() const {
    return rideHistory;
}

void Driver::addRating(double rating) {
    ratings.push_back(rating);
}

double Driver::getRating() const {
    if (ratings.empty()) return 0.0;
    return accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
}

std::string Driver::getName() const {
    return name;
}

std::vector<Driver> Driver::getAvailableDrivers(const Location& pickupLocation) {
    vector<Driver> availableDrivers;
    ifstream file("driverdata.txt");
    string driverID, name, phoneNumber, password, vehicleRegistration;
    double ratePerKm, latitude, longitude;
    bool available;
    while (file >> driverID >> name >> phoneNumber >> password >> vehicleRegistration >> ratePerKm >> latitude >> longitude >> available) {
        if (available && sqrt(pow(latitude - pickupLocation.getX(), 2) + pow(longitude - pickupLocation.getY(), 2)) <= 7) {
            Driver driver(name, password, vehicleRegistration, phoneNumber, ratePerKm);
            driver.updateLocation(latitude, longitude);
            driver.setAvailability(available);
            availableDrivers.push_back(driver);
        }
    }
    return availableDrivers;
}

std::string Driver::generateDriverID(const std::string& name, const std::string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.size() - 2) + to_string(rand() % 1000);
}

void Driver::saveDriverData() const {
    ofstream file(driverID + ".txt");
    if (!file) {
        throw runtime_error("Unable to save driver data.");
    }
    file << driverID << endl;
    file << name << endl;
    file << phoneNumber << endl;
    file << password << endl;
    file << vehicleRegistration << endl;
    file << ratePerKm << endl;
    file << latitude << endl;
    file << longitude << endl;
    file << available << endl;
    file.close();
}

bool Driver::loadDriverData(const std::string& driverID, Driver& driver) {
    ifstream file(driverID + ".txt");
    if (!file) {
        return false;
    }
    getline(file, driver.driverID);
    getline(file, driver.name);
    getline(file, driver.phoneNumber);
    getline(file, driver.password);
    getline(file, driver.vehicleRegistration);
    file >> driver.ratePerKm;
    file >> driver.latitude;
    file >> driver.longitude;
    file >> driver.available;
    file.close();
    return true;
}