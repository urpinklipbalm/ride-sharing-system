#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include "../location/Location.h"

class Driver {
private:
    std::string driverID;
    std::string name;
    std::string phoneNumber;
    std::string password;
    std::string vehicleRegistration;
    double ratePerKm;
    double latitude;
    double longitude;
    bool available;
    std::vector<std::pair<int, std::string>> rideHistory; // Pair of ride ID and status
    std::vector<double> ratings;

public:
    Driver();
    Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm);
    void registerDriver();
    bool login(const std::string& driverID, const std::string& password);
    void setAvailability(bool availability);
    bool isAvailable() const;
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
    void addRideToHistory(int rideID, const std::string& status);
    std::vector<std::pair<int, std::string>> getRideHistory() const;
    void addRating(double rating);
    double getRating() const;
    std::string getName() const;
    static std::vector<Driver> getAvailableDrivers(const Location& pickupLocation);
    std::string generateDriverID(const std::string& name, const std::string& phoneNumber) const;
    void saveDriverData() const;
    static bool loadDriverData(const std::string& driverID, Driver& driver);
};

#endif // DRIVER_H