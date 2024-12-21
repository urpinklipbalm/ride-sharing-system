#ifndef RIDEQUEUE_H
#define RIDEQUEUE_H

#include "RideRequest.h"
#include <queue>

class RideQueue {
public:
    RideQueue();
    void addRequest(const RideRequest& request);
    void removeRequest();
    RideRequest processNextRequest();
    bool isEmpty() const;
    size_t size() const;

private:
    std::queue<RideRequest> requests; // Define the requests member variable
};

#endif // RIDEQUEUE_H