#include <iostream>
#include <cmath>
#include <chrono>
#include "user/User.h"
#include "driver/Driver.h"
#include "location/Location.h"
#include "utils/Utils.h"
#include "rides/RideRequest.h"
#include "graph/Graph.h"
#include "data structures/PriorityQueue.h"

using namespace std;

void userInterface();
void driverInterface();

int main() {
    cout << "\n‧₊˚✧  Welcome to the SmartRide  ✧˚₊‧\n" << endl;

    while (true) {
        cout << "\n‧₊˚ ┊ Are you a User or a Driver?\n" << endl;
        cout << "1. User" << endl;
        cout << "2. Driver" << endl;
        cout << "3. Exit" << endl;

        int roleChoice = getValidatedInput(1, 3);
        if (roleChoice == -1) continue;

        if (roleChoice == 1) {
            userInterface();
        } else if (roleChoice == 2) {
            driverInterface();
        } else if (roleChoice == 3) {
            cout << "\nExiting the system\n · · ─ ·𖥸· ─ · ·\n" << endl;
            break;
        }
    }

    return 0;
}

void userInterface() {
    while (true) {
        cout << "\n‧₊˚ ┊ Please choose an option: \n" << endl;
        cout << "1. User Login" << endl;
        cout << "2. User Register" << endl;
        cout << "3. Back" << endl;

        int userChoice = getValidatedInput(1, 3);
        if (userChoice == -1) continue;

        if (userChoice == 1) {
            string userID, password;
            cout << "\n ↳ Enter userID: ";
            cin >> userID;
            cout << " ↳ Enter password: ";
            cin >> password;
            User user;
            if (user.login(userID, password)) {
                cout << "\n₊ ⊹ User logged in successfully ₊ ⊹" << endl; 
                while (true) {
                    cout << "\n‧₊˚ ┊ Please choose an option: \n" << endl;
                    cout << "1. Request Ride" << endl;
                    cout << "2. View Ride History" << endl;
                    cout << "3. View Profile" << endl;
                    cout << "4. Log Out\n" << endl;

                    int userAction = getValidatedInput(1, 4);
                    if (userAction == -1) continue;

                    if (userAction == 1) {
                        Location pickup = Location::getLocationFromInput();
                        if (!Location::isValidLocation(pickup.getX(), pickup.getY())) {
                            cout << "Invalid pickup location!" << endl;
                            continue;
                        }

                        // Clear the input buffer before reading the next input
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        Location destination = Location::getLocationFromInput();
                        if (!Location::isValidLocation(destination.getX(), destination.getY())) {
                            cout << "Invalid drop-off location!" << endl;
                            continue;
                        } 

                        // Add edge from pickup to destination
                        Location::addEdge(pickup.getX(), pickup.getY(), destination.getX(), destination.getY(), pickup.distanceTo(destination));

                        double distance = pickup.distanceTo(destination);
                        cout << "\n૮₍˶ᵔᵕᵔ˶₎ა Ride requested from " << pickup.getName() << " to " << destination.getName() << " (" << distance << " km)" << endl;

                        // Show available drivers
                        vector<Driver> availableDrivers = Driver::getAvailableDrivers(pickup);
                        if (availableDrivers.empty()) {
                            cout << "\nNo drivers available." << endl;
                        } else {
                            // Sort drivers by rating using a priority queue
                            PriorityQueue<Driver> driverQueue;
                            for (const auto& driver : availableDrivers) {
                                driverQueue.push(driver);
                            }

                            cout << "\n‧₊˚ ┊ Available drivers:" << endl;
                            vector<Driver> sortedDrivers;
                            while (!driverQueue.isEmpty()) {
                                sortedDrivers.push_back(driverQueue.pop());
                            }

                            // Get the current time of day
                            auto now = chrono::system_clock::now();
                            time_t now_c = chrono::system_clock::to_time_t(now);
                            tm local_tm = *localtime(&now_c);
                            int currentHour = local_tm.tm_hour;

                            for (size_t i = 0; i < sortedDrivers.size(); ++i) {
                                double fare = sortedDrivers[i].calculateFare(distance, currentHour, false, 1.0); // Example values for surgePricing and trafficFactor
                                fare = round(fare * 4) / 4.0; // Round to the nearest quarter
                                cout << i + 1 << ". " << sortedDrivers[i].getName() << " (Rating: " << sortedDrivers[i].getRating() << ", Fare: $" << fare << ")" << endl;
                            }

                            cout << "\n‧₊˚ ┊ Select a driver: ";
                            int driverIndex;
                            cin >> driverIndex;
                            if (driverIndex < 1 || driverIndex > sortedDrivers.size()) {
                                cout << "Invalid driver selection." << endl;
                            } else {
                                Driver selectedDriver = sortedDrivers[driverIndex - 1];
                                cout << " ↳ Driver " << selectedDriver.getName() << " selected! " << endl;

                                // Calculate fare
                                double fare = selectedDriver.calculateFare(distance, currentHour, false, 1.0); // Example values for surgePricing and trafficFactor
                                fare = round(fare * 4) / 4.0; // Round to the nearest quarter
                                cout << " ↳ Fare: $" << fare << endl;

                                // Simulate ride completion
                                cout << "\n˗ˏˋ Ride completed. Please rate your driver (1-5): ";
                                double rating;
                                cin >> rating;
                                selectedDriver.addRating(rating);
                                Driver::updateDriverData(selectedDriver); // Update driver data in file
                                cout << "\nThank you for your feedback!\n      · · ─ ·𖥸· ─ · ·" << endl;

                                // Update driver location to drop-off location
                                selectedDriver.updateLocation(destination.getX(), destination.getY());

                                // Update user location to drop-off location
                                user.updateLocation(destination.getX(), destination.getY());

                                // Add ride to user and driver history
                                user.addRideToHistory(1, "Completed", pickup, destination, selectedDriver.getName());
                                selectedDriver.addRideToHistory(1, "Completed", pickup, destination, fare);
                            }
                        }
                    } else if (userAction == 2) {
                        vector<tuple<int, string, Location, Location, string>> history = user.getRideHistory();
                        cout << "‧₊˚ ┊ Ride History:" << endl;
                        for (const auto& ride : history) {
                            cout << "\n → Ride ID: " << get<0>(ride) << "\nStatus: " << get<1>(ride) 
                                 << "\nPickup: " << get<2>(ride).getName() << "\nDestination: " << get<3>(ride).getName()
                                 << "\nDriver: " << get<4>(ride) << endl;
                        }
                        cout << "══════════════════════════" << endl;
                    } else if (userAction == 3) {
                        user.viewProfile();
                    } else if (userAction == 4) {
                        break;
                    }
                }
            }
        } else if (userChoice == 2) {
            string name, phoneNumber, password;
            cout << " → Enter name: ";
            cin >> name;
            cout << " → Enter phone number: ";
            cin >> phoneNumber;
            cout << " → Enter password: ";
            cin >> password;
            User user(name, phoneNumber, password);
            user.registerUser();
        } else if (userChoice == 3) {
            break;
        }
    }
}

void driverInterface() {
    while (true) {
        cout << "‧₊˚ ┊ Please choose an option: " << endl;
        cout << "1. Driver Login" << endl;
        cout << "2. Driver Register" << endl;
        cout << "3. Back" << endl;

        int driverChoice = getValidatedInput(1, 3);
        if (driverChoice == -1) continue;

        if (driverChoice == 1) {
            string driverID, password;
            cout << " → Enter driverID: ";
            cin >> driverID;
            cout << " → Enter password: ";
            cin >> password;
            Driver driver;
            if (driver.login(driverID, password)) {
                // Ask for location if not already set
                if (driver.getLocation() == make_pair(0.0, 0.0)) {
                    Location location = Location::getLocationFromInput();
                    if (!location.isValid()) {
                        cout << ".ᐟ Invalid location!" << endl;
                    } else {
                        driver.updateLocation(location.getX(), location.getY());
                        cout << "\n . ݁₊ ⊹ Location updated." << endl;
                    }
                }

                while (true) {
                    cout << "‧₊˚ ┊ Please choose an option: " << endl;
                    cout << "1. Set Availability" << endl;
                    cout << "2. Update Location" << endl;
                    cout << "3. View Profile" << endl;
                    cout << "4. View Ride History" << endl;
                    cout << "5. Log Out" << endl;

                    int driverAction = getValidatedInput(1, 5);
                    if (driverAction == -1) continue;

                    if (driverAction == 1) {
                        bool availability;
                        cout << "\n → Enter availability (1 for available, 0 for unavailable): ";
                        cin >> availability;
                        driver.setAvailability(availability);
                        cout << "\n˗ˏˋAvailability updated." << endl;
                    } else if (driverAction == 2) {
                        Location location = Location::getLocationFromInput();
                        if (!location.isValid()) {
                            cout << "\n.ᐟ Invalid location!" << endl;
                        } else {
                            driver.updateLocation(location.getX(), location.getY());
                            cout << "\n . ݁₊ ⊹ Location updated." << endl;
                        }
                    } else if (driverAction == 3) {
                        driver.viewProfile();
                    } else if (driverAction == 4) {
                        vector<tuple<int, string, Location, Location, double>> history = driver.getRideHistory();
                        cout << "‧₊˚ ┊ Ride History:" << endl;
                        for (const auto& ride : history) {
                            cout << " → Ride ID: " << get<0>(ride) << ", \nStatus: " << get<1>(ride) 
                                 << ", \nPickup: (" << get<2>(ride).getX() << ", " << get<2>(ride).getY() << ")"
                                 << ", \nDestination: (" << get<3>(ride).getX() << ", " << get<3>(ride).getY() << ")"
                                 << ", \nFare: $" << get<4>(ride) << endl;
                        }
                    } else if (driverAction == 5) {
                        break;
                    }
                }
            }
        } else if (driverChoice == 2) {
            string name, phoneNumber, password, vehicleRegistration;
            double ratePerKm;
            cout << " → Enter name: ";
            cin >> name;
            cout << " → Enter phone number: ";
            cin >> phoneNumber;
            cout << " → Enter password: ";
            cin >> password;
            cout << " → Enter vehicle registration: ";
            cin >> vehicleRegistration;
            cout << " → Enter rate per km: ";
            cin >> ratePerKm;
            Driver driver(name, password, vehicleRegistration, phoneNumber, ratePerKm);
            driver.registerDriver();
        } else if (driverChoice == 3) {
            break;
        }
    }
}