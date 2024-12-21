#ifndef TRAFFICUPDATES_H
#define TRAFFICUPDATES_H

#include <string>
#include <unordered_map>

class TrafficUpdates {
public:
    void updateTrafficData(const std::string& location, const std::string& status);
    std::string getTrafficStatus(const std::string& location) const;
    void displayAllTrafficUpdates() const;

private:
    std::unordered_map<std::string, std::string> trafficData;
};

#endif // TRAFFICUPDATES_H