// filepath: /Users/asma/Desktop/📎/nust/sophmore/data structure + algorithms/project/ride-sharing-system/src/pricing/Pricing.h
#ifndef PRICING_H
#define PRICING_H

#include <vector>
#include <map>

class Pricing {
public:
    Pricing();
    double calculatePrice(double distance, int timeOfDay, bool surgePricing, double trafficFactor) const; // Mark as const
    void addHistoricalPrice(double price);
    std::vector<double> getHistoricalPrices() const;

private:
    std::vector<double> historicalPrices;
    std::map<int, double> timeOfDayMultiplier; // Multiplier based on time of day
    double baseRate;
    double perMileRate;
    double perMinuteRate;
    double surgeMultiplier;
    double trafficMultiplier;
};

#endif // PRICING_H