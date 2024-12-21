#include "RideRequest.h"
#include <cmath>
#include <ctime>

RideRequest::RideRequest() 
    : requestID(0), userLatitude(0.0), userLongitude(0.0), destinationLatitude(0.0), destinationLongitude(0.0) {}

RideRequest::RideRequest(int id, double userLatitude, double userLongitude, double destinationLatitude, double destinationLongitude)
    : requestID(id), userLatitude(userLatitude), userLongitude(userLongitude), destinationLatitude(destinationLatitude), destinationLongitude(destinationLongitude) {}

int RideRequest::getRequestID() const {
    return requestID;
}

double RideRequest::getUserLatitude() const {
    return userLatitude;
}

double RideRequest::getUserLongitude() const {
    return userLongitude;
}

double RideRequest::getDestinationLatitude() const {
    return destinationLatitude;
}

double RideRequest::getDestinationLongitude() const {
    return destinationLongitude;
}

double RideRequest::calculateDistance() const {
    const double R = 6371.0; // Radius of the Earth in kilometers
    double lat1 = userLatitude * M_PI / 180.0;
    double lon1 = userLongitude * M_PI / 180.0;
    double lat2 = destinationLatitude * M_PI / 180.0;
    double lon2 = destinationLongitude * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dlon / 2) * sin(dlon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c; // Distance in kilometers
}



void RideRequest::createRequest(int id, double userLat, double userLon, double destLat, double destLon) {
    requestID = id;
    userLatitude = userLat;
    userLongitude = userLon;
    destinationLatitude = destLat;
    destinationLongitude = destLon;
}

double RideRequest::calculatePrice() const {
    double baseFare = 5.0; // Base fare in dollars
    double costPerKm = 1.5; // Cost per kilometer in dollars
    double distance = calculateDistance();

    // Dynamic pricing factors
    double timeFactor = 1.0;
    double demandFactor = 1.0;

    // Example: Increase price during peak hours (5 PM to 8 PM)
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    if (now->tm_hour >= 17 && now->tm_hour <= 20) {
        timeFactor = 1.5;
    }

    // Example: Increase price if demand is high (this would typically come from a real-time system)
    // demandFactor = getDemandFactor();

    return baseFare + (costPerKm * distance * timeFactor * demandFactor);
}

// double RideRequest::calculatePrice() const {
//     double distance = calculateDistance();
//     const double baseFare = 2.50; // Base fare in dollars
//     const double costPerKm = 1.25; // Cost per kilometer in dollars
//     return baseFare + (distance * costPerKm);
// }