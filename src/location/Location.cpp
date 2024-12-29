#include "Location.h"
#include "Graph.h"
#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

Graph Location::graph;

map<string, vector<Location>> Location::facilities = {
    {"Lake Park", {Location(1, 1, "Lake Park"), Location(1, 3, "Lake Park"), Location(1, 5, "Lake Park"), Location(3, 1, "Lake Park"), Location(3, 3, "Lake Park"), Location(3, 5, "Lake Park")}},
    {"West Mall", {Location(1, 7, "West Mall"), Location(1, 9, "West Mall"), Location(1, 11, "West Mall"), Location(1, 13, "West Mall")}},
    {"Primary School", {Location(1, 15, "Primary School"), Location(1, 17, "Primary School"), Location(1, 19, "Primary School")}},
    {"Housing Complex A", {Location(3, 7, "Housing Complex A"), Location(3, 9, "Housing Complex A"), Location(3, 11, "Housing Complex A"), Location(3, 13, "Housing Complex A"), Location(3, 15, "Housing Complex A"), Location(3, 17, "Housing Complex A"), Location(3, 19, "Housing Complex A"), Location(5, 9, "Housing Complex A"), Location(5, 11, "Housing Complex A"), Location(5, 13, "Housing Complex A"), Location(5, 15, "Housing Complex A"), Location(5, 17, "Housing Complex A"), Location(5, 19, "Housing Complex A"), Location(7, 9, "Housing Complex A"), Location(7, 11, "Housing Complex A"), Location(7, 13, "Housing Complex A"), Location(7, 15, "Housing Complex A"), Location(7, 17, "Housing Complex A"), Location(7, 19, "Housing Complex A")}},
    {"Middle School", {Location(5, 1, "Middle School"), Location(5, 3, "Middle School"), Location(5, 5, "Middle School"), Location(5, 7, "Middle School"), Location(7, 1, "Middle School"), Location(7, 3, "Middle School")}},
    {"Grocery A", {Location(7, 5, "Grocery A"), Location(7, 7, "Grocery A")}},
    {"Swan Park", {Location(9, 1, "Swan Park"), Location(9, 3, "Swan Park"), Location(9, 5, "Swan Park"), Location(9, 7, "Swan Park"), Location(11, 1, "Swan Park"), Location(11, 3, "Swan Park"), Location(11, 5, "Swan Park"), Location(11, 7, "Swan Park")}},
    {"Private Hospital", {Location(9, 9, "Private Hospital"), Location(9, 11, "Private Hospital"), Location(9, 13, "Private Hospital"), Location(9, 15, "Private Hospital"), Location(9, 17, "Private Hospital"), Location(9, 19, "Private Hospital")}},
    {"North Mall", {Location(11, 9, "North Mall"), Location(11, 11, "North Mall"), Location(11, 13, "North Mall"), Location(11, 15, "North Mall"), Location(11, 17, "North Mall"), Location(11, 19, "North Mall")}},
    {"Housing Complex B", {Location(13, 1, "Housing Complex B"), Location(13, 3, "Housing Complex B"), Location(13, 5, "Housing Complex B"), Location(13, 7, "Housing Complex B"), Location(13, 9, "Housing Complex B"), Location(13, 11, "Housing Complex B"), Location(13, 13, "Housing Complex B"), Location(15, 3, "Housing Complex B"), Location(15, 5, "Housing Complex B"), Location(15, 7, "Housing Complex B"), Location(15, 9, "Housing Complex B"), Location(15, 11, "Housing Complex B"), Location(15, 13, "Housing Complex B"), Location(17, 3, "Housing Complex B"), Location(17, 5, "Housing Complex B"), Location(17, 7, "Housing Complex B"), Location(17, 9, "Housing Complex B"), Location(17, 11, "Housing Complex B"), Location(17, 13, "Housing Complex B")}},
    {"High School", {Location(13, 15, "High School"), Location(13, 17, "High School"), Location(13, 19, "High School"), Location(15, 19, "High School"), Location(17, 19, "High School")}},
    {"Public Hospital", {Location(15, 15, "Public Hospital"), Location(15, 17, "Public Hospital"), Location(17, 15, "Public Hospital"), Location(17, 17, "Public Hospital")}},
    {"Grocery B", {Location(15, 1, "Grocery B"), Location(17, 1, "Grocery B"), Location(19, 1, "Grocery B"), Location(19, 3, "Grocery B")}},
    {"Happy Park", {Location(19, 5, "Happy Park"), Location(19, 7, "Happy Park"), Location(19, 9, "Happy Park"), Location(19, 11, "Happy Park"), Location(19, 13, "Happy Park"), Location(19, 15, "Happy Park")}},
    {"Eastside Mall", {Location(19, 17, "Eastside Mall"), Location(19, 19, "Eastside Mall")}}
};

Location::Location() : x(0), y(0), name("invalid"), valid(false) {}

Location::Location(int x, int y, const std::string& name) : x(x), y(y), name(name), valid(true) {}

int Location::getX() const {
    return x;
}

int Location::getY() const {
    return y;
}

std::string Location::getName() const {
    return name;
}

bool Location::isValid() const {
    return valid;
}

double Location::distanceTo(const Location& other) const {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Location Location::getLocationFromInput() {
    string input;
    cout << "⚲ Enter location (coordinates): ";
    getline(cin >> ws, input);

    if (input.find(',') != string::npos) {
        stringstream ss(input);
        string xStr, yStr;
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');
        try {
            int x = stoi(xStr);
            int y = stoi(yStr);
            return getLocationByCoordinates(x, y);
        } catch (const invalid_argument& e) {
            return Location();
        }
    } else {
        return Location();
    }
}

Location Location::getLocationByCoordinates(int x, int y) {
    for (const auto& facility : facilities) {
        for (const auto& loc : facility.second) {
            if (loc.getX() == x && loc.getY() == y) {
                return loc;
            }
        }
    }
    return Location(x, y, "Unknown Location");
}

Location Location::getLocationByName(const std::string& name) {
    for (const auto& facility : facilities) {
        if (strcasecmp(facility.first.c_str(), name.c_str()) == 0) {
            const auto& locations = facility.second;
            srand(time(0));
            int randomIndex = rand() % locations.size();
            return locations[randomIndex];
        }
    }
    return Location();
}

bool Location::isValidLocation(int x, int y) {
    if (x % 2 == 0 || y % 2 == 0 || x < 1 || x > 19 || y < 1 || y > 19) {
        return false;
    }
    for (const auto& facility : facilities) {
        for (const auto& loc : facility.second) {
            if (loc.getX() == x && loc.getY() == y) {
                return true;
            }
        }
    }
    return false;
}

void Location::addEdge(int x1, int y1, int x2, int y2, double weight) {
    int u = x1 * 100 + y1;
    int v = x2 * 100 + y2;
    graph.addEdge(u, v, weight);
}

std::vector<Location> Location::findShortestPath(const Location& start, const Location& goal) {
    int startID = start.getX() * 100 + start.getY();
    int goalID = goal.getX() * 100 + goal.getY();
    std::vector<int> pathIDs = graph.dijkstra(startID, goalID);

    std::vector<Location> path;
    for (int id : pathIDs) {
        int x = id / 100;
        int y = id % 100;
        path.push_back(getLocationByCoordinates(x, y));
    }
    return path;
}