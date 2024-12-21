#include "TrafficUpdates.h"
#include <iostream>

void TrafficUpdates::updateTrafficData(const std::string& location, const std::string& status) {
    trafficData[location] = status;
}

std::string TrafficUpdates::getTrafficStatus(const std::string& location) const {
    auto it = trafficData.find(location);
    if (it != trafficData.end()) {
        return it->second;
    }
    return "No data available";
}

void TrafficUpdates::displayAllTrafficUpdates() const {
    for (const auto& entry : trafficData) {
        std::cout << "Location: " << entry.first << " - Status: " << entry.second << std::endl;
    }
}