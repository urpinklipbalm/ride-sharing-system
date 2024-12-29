#include "Driver.h"
#include "../bloom_filter/BloomFilter.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <numeric>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

int Driver::driverCount = 0;
BloomFilter Driver::availabilityFilter(1000, 5); // Adjust size and number of hashes as needed

Driver::Driver() : latitude(0), longitude(0), available(true), rating(0.0), totalRatings(0), totalCompletedRides(0), ratingSystem(this, 0.0) {}

Driver::Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm)
    : name(name), password(password), vehicleRegistration(vehicleRegistration), phoneNumber(phoneNumber), ratePerKm(ratePerKm), latitude(0), longitude(0), available(true), rating(0.0), totalRatings(0), totalCompletedRides(0), ratingSystem(this, 0.0) {
    driverID = generateDriverID(name, phoneNumber);
    availabilityFilter.add(driverID);
}

void Driver::registerDriver() {
    saveDriverData();
    cout << "\n꩜ .ᐟ Driver registered successfully. Your driverID is: " << driverID << endl;
}

bool Driver::login(const std::string& driverID, const std::string& password) {
    Driver driver;
    // cout << "Attempting to load driver data for ID: " << driverID << endl; // Debug print
    if (loadDriverData(driverID, driver)) {
        // cout << "Driver data loaded. Checking password..." << endl; // Debug print
        if (driver.password == password) {
            *this = driver;
            cout << "\n⊹ ࣪ ˖ Login successful." << endl; // Debug print
            return true;
        } else {
            cout << " .ᐟ Password mismatch." << endl; // Debug print
        }
    } else {
        cout << " .ᐟ Driver ID not found." << endl; // Debug print
    }
    cout << "Invalid driverID or password." << endl;
    return false;
}

void Driver::setAvailability(bool availability) {
    available = availability;
    if (availability) {
        availabilityFilter.add(driverID);
    }
    updateDriverData(*this);
}

bool Driver::isAvailable() const {
    return available; // Check the member variable directly
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
    updateDriverData(*this); // Ensure the driver data is updated in the file
}

std::vector<std::tuple<int, std::string, Location, Location, double>> Driver::getRideHistory() const {
    return rideHistory;
}

std::string Driver::getDriverID() const {
    return driverID; // Assuming driverID is a member of Driver class
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

bool Driver::loadDriverData(const std::string& driverID, Driver& driver) {
    ifstream file("src/driverdata.txt");
    if (!file) {
        cout << " .ᐟ Failed to open driverdata.txt" << endl; // Debug print
        return false;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, phone, pass, vehicleReg;
        double rate, lat, lon, rating;
        int totalRatings, totalCompletedRides;
        bool avail;
        if (!(iss >> id >> name >> phone >> pass >> vehicleReg >> rate >> lat >> lon >> avail >> rating >> totalRatings >> totalCompletedRides)) {
            continue; // Skip lines that don't match the expected format
        }
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

            // Load ride history
            driver.rideHistory.clear();
            string status;
            int rideID, pickupX, pickupY, destinationX, destinationY;
            double fare;
            while (iss >> rideID >> status >> pickupX >> pickupY >> destinationX >> destinationY >> fare) {
                Location pickup(pickupX, pickupY, Location::getLocationByCoordinates(pickupX, pickupY).getName());
                Location destination(destinationX, destinationY, Location::getLocationByCoordinates(destinationX, destinationY).getName());
                driver.rideHistory.push_back({rideID, status, pickup, destination, fare});
            }

            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

vector<Driver> Driver::getAvailableDrivers(const Location& pickupLocation) {
    vector<Driver> availableDrivers;
    ifstream file("src/driverdata.txt");
    if (!file) {
        throw runtime_error(" .ᐟ Unable to open driver data file.");
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, name, phone, pass, vehicleReg;
        double rate, lat, lon, rating;
        int totalRatings, totalCompletedRides;
        bool avail;
        if (!(iss >> id >> name >> phone >> pass >> vehicleReg >> rate >> lat >> lon >> avail >> rating >> totalRatings >> totalCompletedRides)) {
            continue; // Skip lines that don't match the expected format
        }
        cout << "Checking driver: " << id << ", Available: " << avail << ", Location: (" << lat << ", " << lon << ")" << endl; // Debug print
        if (avail) {
            Driver driver;
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

            // Load ride history
            driver.rideHistory.clear();
            string status;
            int rideID, pickupX, pickupY, destinationX, destinationY;
            double fare;
            while (iss >> rideID >> status >> pickupX >> pickupY >> destinationX >> destinationY >> fare) {
                Location pickup(pickupX, pickupY, Location::getLocationByCoordinates(pickupX, pickupY).getName());
                Location destination(destinationX, destinationY, Location::getLocationByCoordinates(destinationX, destinationY).getName());
                driver.rideHistory.push_back({rideID, status, pickup, destination, fare});
            }

            double distanceToPickup = sqrt(pow(lat - pickupLocation.getX(), 2) + pow(lon - pickupLocation.getY(), 2));
            cout << "Distance to pickup: " << distanceToPickup << " km" << endl; // Debug print
            if (distanceToPickup <= 7.0) { // Assuming 7 km radius
                availableDrivers.push_back(driver);
                cout << "Driver " << id << " is within the radius and available." << endl; // Debug print
            } else {
                cout << "Driver " << id << " is not within the radius." << endl; // Debug print
            }
        } else {
            cout << "Driver " << id << " is not available." << endl; // Debug print
        }
    }
    file.close();
    return availableDrivers;
}

std::string Driver::generateDriverID(const std::string& name, const std::string& phoneNumber) const {
    return name + phoneNumber.substr(phoneNumber.size() - 2) + to_string(driverCount++);
}

void Driver::saveDriverData() const {
    ofstream file("src/driverdata.txt", ios::app);
    if (!file) {
        throw runtime_error(" .ᐟ Unable to save driver data.");
    }
    file << driverID << " " << name << " " << phoneNumber << " " << password << " " << vehicleRegistration << " " << ratePerKm << " " << latitude << " " << longitude << " " << available << " " << rating << " " << totalRatings << " " << totalCompletedRides;
    for (const auto& ride : rideHistory) {
        file << " " << get<0>(ride) << " " << get<1>(ride) << " " << get<2>(ride).getX() << " " << get<2>(ride).getY() << " " << get<3>(ride).getX() << " " << get<3>(ride).getY() << " " << get<4>(ride);
    }
    file << endl;
    file.close();
}

void Driver::updateDriverData(const Driver& driver) {
    ifstream file("src/driverdata.txt");
    ofstream tempFile("src/temp.txt");
    if (!file || !tempFile) {
        throw runtime_error(" .ᐟ Unable to update driver data.");
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id == driver.driverID) {
            tempFile << driver.driverID << " " << driver.name << " " << driver.phoneNumber << " " << driver.password << " " << driver.vehicleRegistration << " " << driver.ratePerKm << " " << driver.latitude << " " << driver.longitude << " " << driver.available << " " << driver.rating << " " << driver.totalRatings << " " << driver.totalCompletedRides;
            for (const auto& ride : driver.rideHistory) {
                tempFile << " " << get<0>(ride) << " " << get<1>(ride) << " " << get<2>(ride).getX() << " " << get<2>(ride).getY() << " " << get<3>(ride).getX() << " " << get<3>(ride).getY() << " " << get<4>(ride);
            }
            tempFile << endl;
        } else {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();
    remove("src/driverdata.txt");
    rename("src/temp.txt", "src/driverdata.txt");
}

void Driver::viewProfile() const {
    cout << "\n‧₊˚ ┊ Driver Profile:" << endl;
    cout << "\nDriver ID: " << driverID << endl;
    cout << "Name: " << name << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Vehicle Registration: " << vehicleRegistration << endl;
    cout << "Rate per Km: " << ratePerKm << endl;
    cout << "Current Location: (" << latitude << ", " << longitude << ")" << endl;
    cout << "Availability: " << (isAvailable() ? "Available" : "Unavailable") << endl; // Use isAvailable method
    cout << "Rating: " << getRating() << endl;
    cout << "\n ˗ˏˋ Ride History: \n" << endl;
    for (const auto& ride : rideHistory) {
        cout << "\n⋆˚࿔ Ride ID: " << get<0>(ride) << "\nStatus: " << get<1>(ride) 
             << "\nFrom " << get<2>(ride).getName() << " to " << get<3>(ride).getName() 
             << "\nFare: $" << get<4>(ride) << endl;
    }
}

double Driver::calculateFare(double distance, int timeOfDay, bool surgePricing, double trafficFactor) const {
    return pricing.calculatePrice(distance, timeOfDay, surgePricing, trafficFactor) * ratePerKm;
}