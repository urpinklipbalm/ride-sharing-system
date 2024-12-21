#ifndef RIDEHISTORY_H
#define RIDEHISTORY_H

#include <vector>
#include <string>

class RideHistory {
public:
    struct Ride {
        std::string rideID;
        std::string userID;
        std::string driverID;
        std::string status;
        std::string timestamp;
    };

    void addRide(const Ride& ride);
    std::vector<Ride> getRideHistory(const std::string& userID) const;

private:
    std::vector<Ride> history;
};

#endif // RIDEHISTORY_H