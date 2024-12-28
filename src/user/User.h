#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <utility>
#include "../location/Location.h"

class User {
private:
    std::string userID;
    std::string name;
    std::string phoneNumber;
    std::string password;
    std::vector<std::tuple<int, std::string, Location, Location, std::string>> rideHistory; // Tuple of ride ID, status, pickup, destination, driver
    double latitude;
    double longitude;
    static int userCount;

public:
    User();
    User(const std::string& name, const std::string& phoneNumber, const std::string& password);
    void registerUser();
    bool login(const std::string& userID, const std::string& password);
    void requestRide(double destinationLatitude, double destinationLongitude);
    void addRideToHistory(int rideID, const std::string& status, const Location& pickup, const Location& destination, const std::string& driver);
    std::vector<std::tuple<int, std::string, Location, Location, std::string>> getRideHistory() const;
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
    std::string generateUserID(const std::string& name, const std::string& phoneNumber) const;
    void saveUserData() const;
    static bool loadUserData(const std::string& userID, User& user);
    static void updateUserData(const User& user);
    void viewProfile() const;
};

#endif // USER_H