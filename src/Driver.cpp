#include "Driver.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

// Placeholder for user credentials
unordered_map<string, string> userCredentials = {
    {"driver1", "password1"},
    {"driver2", "password2"}
};

Driver::Driver(int id, const string& name, const string& password) 
    : driverID(id), name(name), password(password), rating(new Rating(this, 0.0)), latitude(0.0), longitude(0.0), available(false), rate(0.0), destinationLatitude(0.0), destinationLongitude(0.0), inAppPaymentSelected(false), paymentProcessed(false) {}

bool Driver::login(const string& username, const string& password) {
    auto it = userCredentials.find(username);
    if (it != userCredentials.end() && it->second == password) {
        cout << "Login successful for driver " << username << endl;
        return true;
    } else {
        cout << "Login failed for driver " << username << endl;
        return false;
    }
}

bool Driver::acceptRide(int rideRequestID, double userLatitude, double userLongitude) {
    if (isWithinRadius(userLatitude, userLongitude, 5.0) && available) {
        cout << "Ride request " << rideRequestID << " accepted by driver " << name << endl;
        // Additional logic for accepting the ride can be added here
        return true;
    } else {
        cout << "Ride request " << rideRequestID << " rejected by driver " << name << endl;
        return false;
    }
}

int Driver::getDriverID() const {
    return driverID;
}

std::string Driver::getName() const {
    return name;
}

double Driver::getRating() const {
    return rating->getRating();
}

void Driver::setRating(double newRating) {
    rating->setRating(newRating);
}

void Driver::updateLocation(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
    cout << "Driver " << name << " location updated to (" << latitude << ", " << longitude << ")" << endl;
}

std::pair<double, double> Driver::getLocation() const {
    return make_pair(latitude, longitude);
}

bool Driver::completeRide(int rideRequestID) {
    cout << "Ride request " << rideRequestID << " completed by driver " << name << endl;
    // Additional logic for completing the ride can be added here
    return true;
}

void Driver::setAvailability(bool available) {
    this->available = available;
}

bool Driver::isAvailable() const {
    return available;
}

double Driver::getRate() const {
    return rate;
}

void Driver::setRate(double rate) {
    this->rate = rate;
}

void Driver::setDestination(double latitude, double longitude) {
    destinationLatitude = latitude;
    destinationLongitude = longitude;
}

bool Driver::processPayment(double amount) {
    if (inAppPaymentSelected) {
        paymentProcessed = true;
        cout << "Payment of " << amount << " processed for driver " << name << endl;
        return true;
    } else {
        cout << "Payment not processed for driver " << name << endl;
        return false;
    }
}

bool Driver::isWithinRadius(double userLatitude, double userLongitude, double radius) const {
    const double R = 6371.0; // Radius of the Earth in kilometers
    double lat1 = latitude * M_PI / 180.0;
    double lon1 = longitude * M_PI / 180.0;
    double lat2 = userLatitude * M_PI / 180.0;
    double lon2 = userLongitude * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = R * c; // Distance in kilometers

    return distance <= radius;
}

void Driver::setInAppPaymentSelected(bool selected) {
    inAppPaymentSelected = selected;
}

void Driver::setPaymentProcessed(bool processed) {
    paymentProcessed = processed;
}