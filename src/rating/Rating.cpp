#include "../driver/Driver.h"
#include "Rating.h"
#include <numeric>
#include <algorithm>
#include <fstream>
#include <stdexcept>

Rating::Rating(Driver* driver, double rating) : driver(driver), rating(rating) {
    loadRatings();
}

void Rating::setRating(double rating) {
    this->rating = rating;
}

double Rating::getRating() const {
    return rating;
}

void Rating::submitRating(const std::string& driverID, double rating) {
    driverRatings[driverID].push_back(rating);
    double averageRating = getAverageRating(driverID);
    updateTopRatedDrivers(driverID, averageRating);
    saveRatings();
}

double Rating::getAverageRating(const std::string& driverID) {
    const auto& ratings = driverRatings[driverID];
    if (ratings.empty()) return 0.0;
    double sum = std::accumulate(ratings.begin(), ratings.end(), 0.0);
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

void Rating::saveRatings() const {
    std::ofstream file("ratings.txt");
    if (!file) {
        throw std::runtime_error("\n⊘ Unable to save ratings data.");
    }
    for (const auto& entry : driverRatings) {
        file << entry.first;
        for (const auto& rating : entry.second) {
            file << " " << rating;
        }
        file << std::endl;
    }
    file.close();
}

void Rating::loadRatings() {
    std::ifstream file("ratings.txt");
    if (!file) {
        return;
    }
    std::string driverID;
    double rating;
    while (file >> driverID) {
        std::vector<double> ratings;
        while (file.peek() != '\n' && file >> rating) {
            ratings.push_back(rating);
        }
        driverRatings[driverID] = ratings;
    }
    file.close();
}