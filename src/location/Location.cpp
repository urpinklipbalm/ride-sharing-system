#include "Location.h"
#include <iostream>
#include <cmath>

using namespace std;

map<string, vector<Location>> Location::facilities = {
    {"lake park", {{1, 1, "lake park"}, {1, 3, "lake park"}, {1, 5, "lake park"}, {3, 1, "lake park"}, {3, 3, "lake park"}, {3, 5, "lake park"}}},
    {"west mall", {{1, 7, "west mall"}, {1, 9, "west mall"}, {1, 11, "west mall"}, {1, 13, "west mall"}}},
    {"primary school", {{1, 15, "primary school"}, {1, 17, "primary school"}, {1, 19, "primary school"}}},
    {"housing complex a", {{3, 7, "housing complex a"}, {3, 9, "housing complex a"}, {3, 11, "housing complex a"}, {3, 13, "housing complex a"}, {3, 15, "housing complex a"}, {3, 17, "housing complex a"}, {3, 19, "housing complex a"}, {5, 9, "housing complex a"}, {5, 11, "housing complex a"}, {5, 13, "housing complex a"}, {5, 15, "housing complex a"}, {5, 17, "housing complex a"}, {5, 19, "housing complex a"}, {7, 9, "housing complex a"}, {7, 11, "housing complex a"}, {7, 13, "housing complex a"}, {7, 15, "housing complex a"}, {7, 17, "housing complex a"}, {7, 19, "housing complex a"}}},
    {"middle school", {{5, 1, "middle school"}, {5, 3, "middle school"}, {5, 5, "middle school"}, {5, 7, "middle school"}, {7, 1, "middle school"}, {7, 3, "middle school"}}},
    {"grocery a", {{7, 5, "grocery a"}, {7, 7, "grocery a"}}},
    {"swan park", {{9, 1, "swan park"}, {9, 3, "swan park"}, {9, 5, "swan park"}, {9, 7, "swan park"}, {11, 1, "swan park"}, {11, 3, "swan park"}, {11, 5, "swan park"}, {11, 7, "swan park"}}},
    {"private hospital", {{9, 9, "private hospital"}, {9, 11, "private hospital"}, {9, 13, "private hospital"}, {9, 15, "private hospital"}, {9, 17, "private hospital"}, {9, 19, "private hospital"}}},
    {"north mall", {{11, 9, "north mall"}, {11, 11, "north mall"}, {11, 13, "north mall"}, {11, 15, "north mall"}, {11, 17, "north mall"}, {11, 19, "north mall"}}},
    {"housing complex b", {{13, 1, "housing complex b"}, {13, 3, "housing complex b"}, {13, 5, "housing complex b"}, {13, 7, "housing complex b"}, {13, 9, "housing complex b"}, {13, 11, "housing complex b"}, {13, 13, "housing complex b"}, {15, 3, "housing complex b"}, {15, 5, "housing complex b"}, {15, 7, "housing complex b"}, {15, 9, "housing complex b"}, {15, 11, "housing complex b"}, {15, 13, "housing complex b"}, {17, 3, "housing complex b"}, {17, 5, "housing complex b"}, {17, 7, "housing complex b"}, {17, 9, "housing complex b"}, {17, 11, "housing complex b"}, {17, 13, "housing complex b"}}},
    {"high school", {{13, 15, "high school"}, {13, 17, "high school"}, {13, 19, "high school"}, {15, 19, "high school"}, {17, 19, "high school"}}},
    {"public hospital", {{15, 15, "public hospital"}, {15, 17, "public hospital"}, {17, 15, "public hospital"}, {17, 17, "public hospital"}}},
    {"grocery b", {{15, 1, "grocery b"}, {17, 1, "grocery b"}, {19, 1, "grocery b"}, {19, 3, "grocery b"}}},
    {"happy park", {{19, 5, "happy park"}, {19, 7, "happy park"}, {19, 9, "happy park"}, {19, 11, "happy park"}, {19, 13, "happy park"}, {19, 15, "happy park"}}},
    {"eastside mall", {{19, 17, "eastside mall"}, {19, 19, "eastside mall"}}}
};

Location::Location() : x(0), y(0), name("") {}

Location::Location(int x, int y, const string& name) : x(x), y(y), name(name) {}

int Location::getX() const {
    return x;
}

int Location::getY() const {
    return y;
}

string Location::getName() const {
    return name;
}

double Location::distanceTo(const Location& other) const {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}

Location Location::getLocationFromInput() {
    int x, y;
    cout << "Enter X coordinate: ";
    cin >> x;
    cout << "Enter Y coordinate: ";
    cin >> y;
    for (const auto& facility : facilities) {
        for (const auto& loc : facility.second) {
            if (loc.getX() == x && loc.getY() == y) {
                return loc;
            }
        }
    }
    return Location(x, y, "invalid");
}

Location Location::getLocationByCoordinates(int x, int y) {
    for (const auto& facility : facilities) {
        for (const auto& loc : facility.second) {
            if (loc.getX() == x && loc.getY() == y) {
                return loc;
            }
        }
    }
    return Location(x, y, "invalid");
}

Location Location::getLocationByName(const string& name) {
    for (const auto& facility : facilities) {
        for (const auto& loc : facility.second) {
            if (loc.getName() == name) {
                return loc;
            }
        }
    }
    return Location(0, 0, "invalid");
}