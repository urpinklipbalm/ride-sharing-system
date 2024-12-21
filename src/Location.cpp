#include "Location.h"
#include <cmath>

Location::Location() : x(0), y(0) {}

Location::Location(double x, double y) : x(x), y(y) {}

void Location::updateLocation(double newX, double newY) {
    x = newX;
    y = newY;
}

double Location::getX() const {
    return x;
}

double Location::getY() const {
    return y;
}

double Location::distanceTo(const Location& other) const {
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}