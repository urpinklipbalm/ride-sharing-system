#include "RideQueue.h"
#include <iostream>

using namespace std;

RideQueue::RideQueue() {}

void RideQueue::addRequest(const RideRequest& request) {
    requests.push(request);
    cout << "Ride request added to the queue." << endl;
}

RideRequest RideQueue::getNextRequest() {
    if (!requests.empty()) {
        RideRequest request = requests.front();
        requests.pop();
        return request;
    }
    return RideRequest(); // Return an empty request if the queue is empty
}

bool RideQueue::isEmpty() const {
    return requests.empty();
}

size_t RideQueue::size() const {
    return requests.size();
}