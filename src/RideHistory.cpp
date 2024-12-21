#include "RideHistory.h"

// Adds a ride to the history
void RideHistory::addRide(const Ride& ride) {
    history.push_back(ride);
}

// Retrieves the entire ride history for a specific user
std::vector<RideHistory::Ride> RideHistory::getRideHistory(const std::string& userID) const {
    std::vector<Ride> userHistory;
    for (const auto& ride : history) {
        if (ride.userID == userID) {
            userHistory.push_back(ride);
        }
    }
    return userHistory;
}