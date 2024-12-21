#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

class RideRequest {
public:
    RideRequest();
    RideRequest(int id, double userLatitude, double userLongitude, double destinationLatitude, double destinationLongitude);
    int getRequestID() const;
    double getUserLatitude() const;
    double getUserLongitude() const;
    double getDestinationLatitude() const;
    double getDestinationLongitude() const;
    double calculateDistance() const;
    double calculatePrice() const;
    void createRequest(int id, double userLat, double userLon, double destLat, double destLon);

private:
    int requestID;
    double userLatitude;
    double userLongitude;
    double destinationLatitude;
    double destinationLongitude;
};

#endif // RIDEREQUEST_H