#include "Driver.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

Driver::Driver(const string& name, const string& password, const string& vehicleRegistration, const string& phoneNumber, double ratePerKm)
    : name(name), password(password), vehicleRegistration(vehicleRegistration), phoneNumber(phoneNumber), rating(0.0), latitude(0.0), longitude(0.0), available(true), ratePerKm(ratePerKm), destinationLatitude(0.0), destinationLongitude(0.0) {
    static int index = 0;
    driverID = generateDriverID(name, phoneNumber, index++);
}

void Driver::registerDriver() {
    saveDriverData();
    cout << "Driver registered successfully! Your driverID is: " << driverID << endl;
}

bool Driver::login(const string& inputDriverID, const string& inputPassword) {
    if (loadDriverData(inputDriverID, *this) && password == inputPassword) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid driverID or password." << endl;
    return false;
}

bool Driver::acceptRide(int rideRequestID, double userLatitude, double userLongitude) {
    if (available && isWithinRadius(userLatitude, userLongitude, 10.0)) {
        cout << "Ride request " << rideRequestID << " accepted by driver " << name << endl;
        setAvailability(false);
        setDestination(userLatitude, userLongitude);
        return true;
    } else {
        cout << "Ride request " << rideRequestID << " cannot be accepted by driver " << name << endl;
        return false;
    }
}

string Driver::getDriverID() const {
    return driverID;
}

string Driver::getName() const {
    return name;
}

double Driver::getRating() const {
    return rating;
}

void Driver::setRating(double newRating) {
    rating = newRating;
}

void Driver::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
    cout << "Driver " << name << " location updated to (" << latitude << ", " << longitude << ")" << endl;
}

pair<double, double> Driver::getLocation() const {
    return make_pair(latitude, longitude);
}

bool Driver::completeRide(int rideRequestID) {
    cout << "Ride request " << rideRequestID << " completed by driver " << name << endl;
    setAvailability(true);
    return true;
}

void Driver::setAvailability(bool available) {
    this->available = available;
}

bool Driver::isAvailable() const {
    return available;
}

double Driver::getRatePerKm() const {
    return ratePerKm;
}

void Driver::setRatePerKm(double rate) {
    this->ratePerKm = rate;
}

void Driver::setDestination(double latitude, double longitude) {
    this->destinationLatitude = latitude;
    this->destinationLongitude = longitude;
}

bool Driver::processPayment(double amount) {
    cout << "Payment of " << amount << " processed for driver " << name << endl;
    return true;
}

bool Driver::isWithinRadius(double userLatitude, double userLongitude, double radius) const {
    double distance = sqrt(pow(latitude - userLatitude, 2) + pow(longitude - userLongitude, 2));
    return distance <= radius;
}

string Driver::generateDriverID(const string& name, const string& phoneNumber, int index) const {
    if (phoneNumber.length() < 3) {
        throw out_of_range("Phone number is too short to generate driverID");
    }
    return name + phoneNumber.substr(phoneNumber.length() - 3) + to_string(index);
}

void Driver::saveDriverData() const {
    ofstream driverDataFile("driverdata.txt", ios::app);
    if (driverDataFile.is_open()) {
        driverDataFile << driverID << " " << name << " " << password << " " << vehicleRegistration << " " << phoneNumber << " " << ratePerKm << endl;
        driverDataFile.close();
    } else {
        cout << "Unable to open file for writing driver data." << endl;
    }
}

bool Driver::loadDriverData(const string& inputDriverID, Driver& driver) {
    ifstream driverDataFile("driverdata.txt");
    string fileDriverID, fileName, filePassword, fileVehicleRegistration, filePhoneNumber;
    double fileRatePerKm;
    if (driverDataFile.is_open()) {
        while (driverDataFile >> fileDriverID >> fileName >> filePassword >> fileVehicleRegistration >> filePhoneNumber >> fileRatePerKm) {
            if (fileDriverID == inputDriverID) {
                driver.driverID = fileDriverID;
                driver.name = fileName;
                driver.password = filePassword;
                driver.vehicleRegistration = fileVehicleRegistration;
                driver.phoneNumber = filePhoneNumber;
                driver.ratePerKm = fileRatePerKm;
                driverDataFile.close();
                return true;
            }
        }
        driverDataFile.close();
    } else {
        cout << "Unable to open file for reading driver data." << endl;
    }
    return false;
}