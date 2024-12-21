#include "Pricing.h"
#include <cmath>
#include <algorithm>

Pricing::Pricing() 
    : baseRate(5.0), perMileRate(2.0), perMinuteRate(0.5), surgeMultiplier(1.5), trafficMultiplier(1.2) {
    // Initialize time of day multipliers (example values)
    timeOfDayMultiplier[0] = 1.0;  // Midnight
    timeOfDayMultiplier[6] = 1.2;  // Early morning
    timeOfDayMultiplier[12] = 1.5; // Noon
    timeOfDayMultiplier[18] = 1.3; // Evening
}

double Pricing::calculatePrice(double distance, int timeOfDay, bool surgePricing, double trafficFactor) {
    double timeMultiplier = 1.0;
    auto it = timeOfDayMultiplier.lower_bound(timeOfDay);
    if (it != timeOfDayMultiplier.end()) {
        timeMultiplier = it->second;
    } else if (!timeOfDayMultiplier.empty()) {
        timeMultiplier = timeOfDayMultiplier.rbegin()->second;
    }

    double price = baseRate + (distance * perMileRate) + (distance * perMinuteRate * timeMultiplier);
    if (surgePricing) {
        price *= surgeMultiplier;
    }
    price *= trafficFactor;

    addHistoricalPrice(price);
    return price;
}

void Pricing::addHistoricalPrice(double price) {
    historicalPrices.push_back(price);
}

std::vector<double> Pricing::getHistoricalPrices() const {
    return historicalPrices;
}