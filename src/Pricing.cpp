#include "Pricing.h"
#include <algorithm>

Pricing::Pricing()
    : baseRate(2.0), perMileRate(1.5), perMinuteRate(0.5), surgeMultiplier(1.5), trafficMultiplier(1.0) {
    timeOfDayMultiplier[0] = 1.0;  // Midnight to 1 AM
    timeOfDayMultiplier[8] = 1.2;  // 8 AM to 9 AM
    timeOfDayMultiplier[17] = 1.3; // 5 PM to 6 PM
    // Adding more time slots as needed!!!!
}

double Pricing::calculatePrice(int distance, int timeOfDay, bool surgePricing, double trafficFactor) {
    double timeMultiplier = 1.0;
    auto it = timeOfDayMultiplier.lower_bound(timeOfDay);
    if (it != timeOfDayMultiplier.end()) {
        timeMultiplier = it->second;
    }

    double price = baseRate + (distance * perMileRate) + (distance * perMinuteRate);
    price *= timeMultiplier;
    if (surgePricing) {
        price *= surgeMultiplier;
    }
    price *= trafficFactor;

    return price;
}

void Pricing::addHistoricalPrice(double price) {
    historicalPrices.push_back(price);
}

std::vector<double> Pricing::getHistoricalPrices() const {
    return historicalPrices;
}