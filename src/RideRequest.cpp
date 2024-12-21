#include "RideRequest.h"
#include <iostream>

using namespace std;

RideRequest::RideRequest() : requestID(0), userLatitude(0.0), userLongitude(0.0), destinationLatitude(0.0), destinationLongitude(0.0) {}

void RideRequest::createRequest(int id, double userLat, double userLon, double destLat, double destLon) {
    requestID = id;
    userLatitude = userLat;
    userLongitude = userLon;
    destinationLatitude = destLat;
    destinationLongitude = destLon;
    cout << "Ride request created with ID: " << requestID << endl;
}

int RideRequest::getID() const {
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