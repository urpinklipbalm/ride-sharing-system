#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <vector>

class Location {
private:
    int x;
    int y;
    std::string name;

public:
    Location();
    Location(int x, int y, const std::string& name);
    int getX() const;
    int getY() const;
    std::string getName() const;
    double distanceTo(const Location& other) const;
    static Location getLocationFromInput();
    static Location getLocationByCoordinates(int x, int y);
    static Location getLocationByName(const std::string& name);
    static std::map<std::string, std::vector<Location>> facilities;
};

#endif // LOCATION_H