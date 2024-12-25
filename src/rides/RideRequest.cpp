#include "RideRequest.h"
#include <cmath>
#include <fstream>

using namespace std;

RideRequest::RideRequest(int id, const Location& pickupLocation, const Location& dropoffLocation)
    : id(id), pickupLocation(pickupLocation), dropoffLocation(dropoffLocation) {}

int RideRequest::getID() const {
    return id;
}

Location RideRequest::getPickupLocation() const {
    return pickupLocation;
}

Location RideRequest::getDropoffLocation() const {
    return dropoffLocation;
}

vector<RideRequest> RideRequest::getRideRequestsWithinRadius(const pair<double, double>& driverLocation, double radius) {
    vector<RideRequest> rideRequests;
    ifstream file("riderequests.txt");
    int id, pickupX, pickupY, dropoffX, dropoffY;
    while (file >> id >> pickupX >> pickupY >> dropoffX >> dropoffY) {
        Location pickupLocation(pickupX, pickupY, "");
        Location dropoffLocation(dropoffX, dropoffY, "");
        if (sqrt(pow(driverLocation.first - pickupX, 2) + pow(driverLocation.second - pickupY, 2)) <= radius) {
            rideRequests.push_back(RideRequest(id, pickupLocation, dropoffLocation));
        }
    }
    return rideRequests;
}