#include "Driver.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <iomanip>

using namespace std;

int Driver::driverCount = 0;

Driver::Driver() : latitude(0), longitude(0), available(true), rating(0.0), totalRatings(0), totalCompletedRides(0), ratingSystem(this, 0.0) {}

Driver::Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm)
    : name(name), password(password), vehicleRegistration(vehicleRegistration), phoneNumber(phoneNumber), ratePerKm(ratePerKm), latitude(0), longitude(0), available(true), rating(0.0), totalRatings(0), totalCompletedRides(0), ratingSystem(this, 0.0) {
    driverID = generateDriverID(name, phoneNumber);
}

void Driver::registerDriver() {
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
    updateDriverData(*this);
}

bool Driver::isAvailable() const {
    return available;
}

void Driver::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
    updateDriverData(*this);
}

std::pair<double, double> Driver::getLocation() const {
    return {latitude, longitude};
}

void Driver::addRideToHistory(int rideID, const std::string& status, const Location& pickup, const Location& destination, double fare) {
    rideHistory.push_back({rideID, status, pickup, destination, fare});
    updateDriverData(*this);
}

std::vector<std::tuple<int, std::string, Location, Location, double>> Driver::getRideHistory() const {
    return rideHistory;
}

void Driver::addRating(double rating) {
    ratingSystem.submitRating(driverID, rating);
    this->rating = ratingSystem.getAverageRating(driverID);
    totalRatings++;
    updateDriverData(*this);
}

double Driver::getRating() const {
    return rating;
}

std::string Driver::getName() const {
    return name;
}

double Driver::getRatePerKm() const {
    return ratePerKm;
}

std::vector<Driver> Driver::getAvailableDrivers(const Location& pickupLocation) {
    vector<Driver> availableDrivers;
    ifstream file("driverdata.txt");
    string driverID, name, phoneNumber, password, vehicleRegistration;
    double ratePerKm, latitude, longitude, rating;
    int totalRatings, totalCompletedRides;
    bool available;
    while (file >> driverID >> name >> phoneNumber >> password >> vehicleRegistration >> ratePerKm >> latitude >> longitude >> available >> rating >> totalRatings >> totalCompletedRides) {
        if (available) {
            double distance = sqrt(pow(latitude - pickupLocation.getX(), 2) + pow(longitude - pickupLocation.getY(), 2));
            Driver driver(name, password, vehicleRegistration, phoneNumber, ratePerKm);
            driver.driverID = driverID;
            driver.latitude = latitude;
            driver.longitude = longitude;
            driver.available = available;
            driver.rating = rating;
            driver.totalRatings = totalRatings;
            driver.totalCompletedRides = totalCompletedRides;
            availableDrivers.push_back(driver);
        }
    }
    file.close();
    return availableDrivers;
}

std::string Driver::generateDriverID(const std::string& name, const std::string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.size() - 2) + to_string(driverCount++);
}

void Driver::saveDriverData() const {
    ofstream file("driverdata.txt", ios::app);
    if (!file) {
        throw runtime_error("Unable to save driver data.");
    }
    file << driverID << " " << name << " " << phoneNumber << " " << password << " " << vehicleRegistration << " " << ratePerKm << " " << latitude << " " << longitude << " " << available << " " << rating << " " << totalRatings << " " << totalCompletedRides << endl;
    file.close();
}

bool Driver::loadDriverData(const std::string& driverID, Driver& driver) {
    ifstream file("driverdata.txt");
    if (!file) {
        return false;
    }
    string id, name, phone, pass, vehicleReg;
    double rate, lat, lon, rating;
    int totalRatings, totalCompletedRides;
    bool avail;
    while (file >> id >> name >> phone >> pass >> vehicleReg >> rate >> lat >> lon >> avail >> rating >> totalRatings >> totalCompletedRides) {
        if (id == driverID) {
            driver.driverID = id;
            driver.name = name;
            driver.phoneNumber = phone;
            driver.password = pass;
            driver.vehicleRegistration = vehicleReg;
            driver.ratePerKm = rate;
            driver.latitude = lat;
            driver.longitude = lon;
            driver.available = avail;
            driver.rating = rating;
            driver.totalRatings = totalRatings;
            driver.totalCompletedRides = totalCompletedRides;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void Driver::updateDriverData(const Driver& driver) {
    ifstream file("driverdata.txt");
    ofstream tempFile("temp.txt");
    if (!file || !tempFile) {
        throw runtime_error("Unable to update driver data.");
    }
    string id, name, phone, pass, vehicleReg;
    double rate, lat, lon, rating;
    int totalRatings, totalCompletedRides;
    bool avail;
    while (file >> id >> name >> phone >> pass >> vehicleReg >> rate >> lat >> lon >> avail >> rating >> totalRatings >> totalCompletedRides) {
        if (id == driver.driverID) {
            tempFile << driver.driverID << " " << driver.name << " " << driver.phoneNumber << " " << driver.password << " " << driver.vehicleRegistration << " " << driver.ratePerKm << " " << driver.latitude << " " << driver.longitude << " " << driver.available << " " << driver.rating << " " << driver.totalRatings << " " << driver.totalCompletedRides << endl;
        } else {
            tempFile << id << " " << name << " " << phone << " " << pass << " " << vehicleReg << " " << rate << " " << lat << " " << lon << " " << avail << " " << rating << " " << totalRatings << " " << totalCompletedRides << endl;
        }
    }
    file.close();
    tempFile.close();
    remove("driverdata.txt");
    rename("temp.txt", "driverdata.txt");
}

void Driver::viewProfile() const {
    cout << "Driver Profile:" << endl;
    cout << "Driver ID: " << driverID << endl;
    cout << "Name: " << name << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Vehicle Registration: " << vehicleRegistration << endl;
    cout << "Rate per Km: " << ratePerKm << endl;
    cout << "Current Location: (" << latitude << ", " << longitude << ")" << endl;
    cout << "Availability: " << (available ? "Available" : "Unavailable") << endl;
    cout << "Rating: " << getRating() << endl;
    cout << "Ride History: " << endl;
    for (const auto& ride : rideHistory) {
        cout << "Ride ID: " << get<0>(ride) << ", Status: " << get<1>(ride) << ", Pickup: (" << get<2>(ride).getX() << ", " << get<2>(ride).getY() << "), Destination: (" << get<3>(ride).getX() << ", " << get<3>(ride).getY() << "), Fare: " << get<4>(ride) << endl;
    }
}

double Driver::calculateFare(double distance, int timeOfDay, bool surgePricing, double trafficFactor) const {
    return pricing.calculatePrice(distance, timeOfDay, surgePricing, trafficFactor) * ratePerKm;
}