#ifndef LOCATION_H
#define LOCATION_H

class Location {
public:
    Location();
    Location(double x, double y);
    void updateLocation(double newX, double newY);
    double getX() const;
    double getY() const;
    double distanceTo(const Location& other) const;

private:
    double x;
    double y;
};

#endif // LOCATION_H