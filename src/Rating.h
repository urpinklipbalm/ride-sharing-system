#ifndef RATING_H
#define RATING_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

class Driver;

class Rating {
public:
    Rating(Driver* driver, double rating);
    void setRating(double rating);
    double getRating() const;
    void submitRating(const std::string& driverID, int rating);
    double getAverageRating(const std::string& driverID);
    std::vector<std::string> getTopRatedDrivers(int topN);

private:
    Driver* driver;
    double rating;
    std::unordered_map<std::string, std::vector<int>> driverRatings; // driverID and their ratings
    std::priority_queue<std::pair<double, std::string>> topRatedDrivers; // max-heap for top-rated drivers

    void updateTopRatedDrivers(const std::string& driverID, double averageRating);
};

#endif // RATING_H