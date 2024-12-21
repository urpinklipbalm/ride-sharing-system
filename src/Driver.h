#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "Rating.h"

class Driver {
public:
    Driver(int id, const std::string& name, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    bool acceptRide(int rideRequestID, double userLatitude, double userLongitude);
    int getDriverID() const;
    std::string getName() const;
    double getRating() const;
    void setRating(double newRating);
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
    bool completeRide(int rideRequestID);
    void setAvailability(bool available);
    bool isAvailable() const;
    double getRate() const;
    void setRate(double rate);
    void setDestination(double latitude, double longitude);
    bool processPayment(double amount);
    bool isWithinRadius(double userLatitude, double userLongitude, double radius) const;
    void setInAppPaymentSelected(bool selected);
    void setPaymentProcessed(bool processed);

private:
    int driverID;
    std::string name;
    std::string password;
    Rating* rating;
    double latitude;
    double longitude;
    bool available;
    double rate;
    double destinationLatitude;
    double destinationLongitude;
    bool inAppPaymentSelected;
    bool paymentProcessed;
};

#endif // DRIVER_H