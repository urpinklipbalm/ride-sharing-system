#include "RideQueue.h"
#include <iostream>

RideQueue::RideQueue() {}

void RideQueue::addRequest(const RideRequest& request) {
    requests.push(request);
}

void RideQueue::removeRequest() {
    if (!requests.empty()) {
        requests.pop();
    } else {
        std::cerr << "No requests to remove." << std::endl;
    }
}

RideRequest RideQueue::processNextRequest() {
    if (!requests.empty()) {
        RideRequest nextRequest = requests.front();
        requests.pop();
        return nextRequest;
    } else {
        std::cerr << "No requests to process." << std::endl;
        return RideRequest(); // Return a default-constructed RideRequest
    }
}

bool RideQueue::isEmpty() const {
    return requests.empty();
}

size_t RideQueue::size() const {
    return requests.size();
}