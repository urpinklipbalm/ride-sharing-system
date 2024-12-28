#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <vector>
#include "Graph.h"

class Location {
private:
    int x;
    int y;
    std::string name;
    bool valid;
    static Graph graph;

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
    static bool isValidLocation(int x, int y);
    bool isValid() const;
    static void addEdge(int x1, int y1, int x2, int y2, double weight);
    static std::vector<Location> findShortestPath(const Location& start, const Location& goal);
};

#endif // LOCATION_H