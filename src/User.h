#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>

class User {
private:
    std::string userID;
    std::string password;
    std::vector<std::pair<int, std::string>> rideHistory; // Pair of ride ID and status
    double latitude;
    double longitude;

public:
    User(const std::string& userID, const std::string& password);
    void registerUser();
    void login();
    bool login(const std::string& username, const std::string& password);
    void requestRide(double destinationLatitude, double destinationLongitude);
    void addRideToHistory(int rideID, const std::string& status);
    std::vector<std::pair<int, std::string>> getRideHistory() const;
    void updateLocation(double latitude, double longitude);
    std::pair<double, double> getLocation() const;
};

#endif // USER_H