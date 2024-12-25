#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

#include "../location/Location.h"
#include <vector>

class RideRequest {
private:
    int id;
    Location pickupLocation;
    Location dropoffLocation;

public:
    RideRequest(int id, const Location& pickupLocation, const Location& dropoffLocation);
    int getID() const;
    Location getPickupLocation() const;
    Location getDropoffLocation() const;
    static std::vector<RideRequest> getRideRequestsWithinRadius(const std::pair<double, double>& driverLocation, double radius);
};

#endif // RIDEREQUEST_H