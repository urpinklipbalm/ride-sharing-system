#ifndef DRIVER_H
#define DRIVER_H
#include <string>
#include <vector>
#include "../location/Location.h"
#include "../pricing/Pricing.h"
#include "../rating/Rating.h"
#include "../bloom_filter/BloomFilter.h"


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
    double rating;
    int totalRatings;
    int totalCompletedRides;
    std::vector<std::tuple<int, std::string, Location, Location, double>> rideHistory;
    static int driverCount;
    Pricing pricing;
    Rating ratingSystem;

public:
    Driver();
    Driver(const std::string& name, const std::string& password, const std::string& vehicleRegistration, const std::string& phoneNumber, double ratePerKm);
    void registerDriver();
    bool login(const std::string& driverID, const std::string& password);
    void setAvailability(bool availability);
    bool isAvailable() const;
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
    void addRideToHistory(int rideID, const std::string& status, const Location& pickup, const Location& destination, double fare);
    std::vector<std::tuple<int, std::string, Location, Location, double>> getRideHistory() const;
    void addRating(double rating);
    double getRating() const;
    std::string getName() const;
    double getRatePerKm() const; // Add this getter method
    static std::vector<Driver> getAvailableDrivers(const Location& pickupLocation);
    std::string generateDriverID(const std::string& name, const std::string& phoneNumber) const;
    void saveDriverData() const;
    static bool loadDriverData(const std::string& driverID, Driver& driver);
    static void updateDriverData(const Driver& driver);
    void viewProfile() const;
    static BloomFilter availabilityFilter;
    std::string getDriverID() const;

    bool operator>(const Driver& other) const {
        return getRating() > other.getRating();
    }

    bool operator<(const Driver& other) const {
        return getRating() < other.getRating();
    }

    double calculateFare(double distance, int timeOfDay, bool surgePricing, double trafficFactor) const;
};

#endif // DRIVER_H