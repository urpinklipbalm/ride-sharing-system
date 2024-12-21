#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <utility>
#include "Rating.h"

class Driver {
private:
    std::string driverID;
    std::string name;
    std::string password;
    std::string vehicleRegistration;
    std::string phoneNumber;
    double rating;
    double latitude;
    double longitude;
    bool available;
    double ratePerKm;
    double destinationLatitude;
    double destinationLongitude;

public:
    Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm);
    void registerDriver();
    bool login(const std::string& driverID, const std::string& password);
    bool acceptRide(int rideRequestID, double userLatitude, double userLongitude);
    std::string getDriverID() const;
    std::string getName() const;
    double getRating() const;
    void setRating(double newRating);
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
    bool completeRide(int rideRequestID);
    void setAvailability(bool available);
    bool isAvailable() const;
    double getRatePerKm() const;
    void setRatePerKm(double rate);
    void setDestination(double latitude, double longitude);
    bool processPayment(double amount);
    bool isWithinRadius(double userLatitude, double userLongitude, double radius) const;
    std::string generateDriverID(const std::string& name, const std::string& phoneNumber, int index) const;
    void saveDriverData() const;
    static bool loadDriverData(const std::string& driverID, Driver& driver);
};

#endif // DRIVER_H