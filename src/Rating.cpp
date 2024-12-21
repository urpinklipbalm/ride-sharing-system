#include "Rating.h"
#include "Driver.h"
#include <numeric>
#include <algorithm>

Rating::Rating(Driver* driver, double rating) : driver(driver), rating(rating) {}

void Rating::setRating(double rating) {
    this->rating = rating;
}

double Rating::getRating() const {
    return rating;
}

void Rating::submitRating(const std::string& driverID, int rating) {
    driverRatings[driverID].push_back(rating);
    double averageRating = getAverageRating(driverID);
    updateTopRatedDrivers(driverID, averageRating);
}

double Rating::getAverageRating(const std::string& driverID) {
    const auto& ratings = driverRatings[driverID];
    if (ratings.empty()) return 0.0;
    double sum = std::accumulate(ratings.begin(), ratings.end(), 0);
    return sum / ratings.size();
}

std::vector<std::string> Rating::getTopRatedDrivers(int topN) {
    std::vector<std::string> topDrivers;
    auto tempQueue = topRatedDrivers;
    while (topN-- > 0 && !tempQueue.empty()) {
        topDrivers.push_back(tempQueue.top().second);
        tempQueue.pop();
    }
    return topDrivers;
}

void Rating::updateTopRatedDrivers(const std::string& driverID, double averageRating) {
    topRatedDrivers.push({averageRating, driverID});
    if (topRatedDrivers.size() > 10) {
        topRatedDrivers.pop();
    }
}