#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

class RideRequest {
private:
    int requestID;
    double userLatitude;
    double userLongitude;
    double destinationLatitude;
    double destinationLongitude;

public:
    RideRequest();
    void createRequest(int id, double userLat, double userLon, double destLat, double destLon);
    int getID() const;
    double getUserLatitude() const;
    double getUserLongitude() const;
    double getDestinationLatitude() const;
    double getDestinationLongitude() const;
};

#endif // RIDEREQUEST_H