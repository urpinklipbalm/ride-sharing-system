#include <iostream>
#include "user/User.h"
#include "driver/Driver.h"
#include "location/Location.h"
#include "utils/Utils.h"
#include "rides/RideRequest.h"

using namespace std;

void userInterface();
void driverInterface();

int main() {
    cout << "Welcome to the Ride-Sharing System!" << endl;

    while (true) {
        cout << "Are you a User or a Driver?" << endl;
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
            cout << "Exiting the system." << endl;
            break;
        }
    }

    return 0;
}

void userInterface() {
    while (true) {
        cout << "Please choose an option: " << endl;
        cout << "1. User Login" << endl;
        cout << "2. User Register" << endl;
        cout << "3. Back" << endl;

        int userChoice = getValidatedInput(1, 3);
        if (userChoice == -1) continue;

        if (userChoice == 1) {
            string userID, password;
            cout << "Enter userID: ";
            cin >> userID;
            cout << "Enter password: ";
            cin >> password;
            User user;
            if (user.login(userID, password)) {
                while (true) {
                    cout << "Please choose an option: " << endl;
                    cout << "1. Request Ride" << endl;
                    cout << "2. View Ride History" << endl;
                    cout << "3. Log Out" << endl;

                    int userAction = getValidatedInput(1, 3);
                    if (userAction == -1) continue;

                    if (userAction == 1) {
                        Location pickup, destination;
                        string input;
                        cout << "Enter pickup location (coordinates or name): ";
                        cin >> input;
                        if (isdigit(input[0])) {
                            int x = stoi(input);
                            int y;
                            cin >> y;
                            pickup = Location::getLocationByCoordinates(x, y);
                        } else {
                            pickup = Location::getLocationByName(input);
                        }

                        if (pickup.getName() == "invalid") {
                            cout << "Invalid pickup location!" << endl;
                            continue;
                        }

                        cout << "Enter drop-off location (coordinates or name): ";
                        cin >> input;
                        if (isdigit(input[0])) {
                            int x = stoi(input);
                            int y;
                            cin >> y;
                            destination = Location::getLocationByCoordinates(x, y);
                        } else {
                            destination = Location::getLocationByName(input);
                        }

                        if (destination.getName() == "invalid") {
                            cout << "Invalid drop-off location!" << endl;
                            continue;
                        }

                        cout << "Enter any special instructions for the driver: ";
                        string specialInstructions;
                        cin.ignore();
                        getline(cin, specialInstructions);

                        double distance = pickup.distanceTo(destination);
                        cout << "Ride requested from " << pickup.getName() << " to " << destination.getName() << " (" << distance << " km)" << endl;

                        // Here you would normally assign a driver and handle the ride request
                        // For simplicity, we'll just add a dummy ride to the user's history
                        user.addRideToHistory(1, "Completed");

                        // Show available drivers
                        vector<Driver> availableDrivers = Driver::getAvailableDrivers(pickup);
                        if (availableDrivers.empty()) {
                            cout << "No drivers available." << endl;
                        } else {
                            cout << "Available drivers:" << endl;
                            for (size_t i = 0; i < availableDrivers.size(); ++i) {
                                cout << i + 1 << ". " << availableDrivers[i].getName() << " (Rating: " << availableDrivers[i].getRating() << ")" << endl;
                            }
                            cout << "Select a driver: ";
                            int driverIndex;
                            cin >> driverIndex;
                            if (driverIndex < 1 || driverIndex > availableDrivers.size()) {
                                cout << "Invalid driver selection." << endl;
                            } else {
                                Driver selectedDriver = availableDrivers[driverIndex - 1];
                                cout << "Driver " << selectedDriver.getName() << " selected." << endl;

                                // Simulate ride completion
                                cout << "Ride completed. Please rate your driver (1-5): ";
                                double rating;
                                cin >> rating;
                                selectedDriver.addRating(rating);
                                cout << "Thank you for your feedback!" << endl;
                            }
                        }
                    } else if (userAction == 2) {
                        vector<pair<int, string>> history = user.getRideHistory();
                        if (history.empty()) {
                            cout << "No rides taken by user yet." << endl;
                        } else {
                            for (const auto &ride : history) {
                                cout << "Ride ID: " << ride.first << ", Status: " << ride.second << endl;
                            }
                        }
                    } else if (userAction == 3) {
                        break;
                    }
                }
            }
        } else if (userChoice == 2) {
            string name, phoneNumber, password;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phoneNumber;
            cout << "Enter password: ";
            cin >> password;
            try {
                User user(name, phoneNumber, password);
                user.registerUser();
            } catch (const out_of_range &e) {
                cout << e.what() << endl;
            }
        } else if (userChoice == 3) {
            break;
        }
    }
}

void driverInterface() {
    while (true) {
        cout << "Please choose an option: " << endl;
        cout << "1. Driver Login" << endl;
        cout << "2. Driver Register" << endl;
        cout << "3. Back" << endl;

        int driverChoice = getValidatedInput(1, 3);
        if (driverChoice == -1) continue;

        if (driverChoice == 1) {
            string driverID, password;
            cout << "Enter driverID: ";
            cin >> driverID;
            cout << "Enter password: ";
            cin >> password;
            Driver driver;
            if (driver.login(driverID, password)) {
                cout << "Enter your current location (coordinates): ";
                int x, y;
                cin >> x >> y;
                driver.updateLocation(x, y);

                while (true) {
                    cout << "Please choose an option: " << endl;
                    cout << "1. Turn Availability On" << endl;
                    cout << "2. Receive Ride Requests" << endl;
                    cout << "3. Log Out" << endl;

                    int driverAction = getValidatedInput(1, 3);
                    if (driverAction == -1) continue;

                    if (driverAction == 1) {
                        driver.setAvailability(true);
                        cout << "Availability turned on." << endl;
                    } else if (driverAction == 2) {
                        vector<RideRequest> rideRequests = RideRequest::getRideRequestsWithinRadius(driver.getLocation(), 7);
                        if (rideRequests.empty()) {
                            cout << "No ride requests available." << endl;
                        } else {
                            cout << "Available ride requests:" << endl;
                            for (size_t i = 0; i < rideRequests.size(); ++i) {
                                cout << i + 1 << ". Pickup: " << rideRequests[i].getPickupLocation().getName() << ", Drop-off: " << rideRequests[i].getDropoffLocation().getName() << endl;
                            }
                            cout << "Select a ride request to accept: ";
                            int requestIndex;
                            cin >> requestIndex;
                            if (requestIndex < 1 || requestIndex > rideRequests.size()) {
                                cout << "Invalid ride request selection." << endl;
                            } else {
                                RideRequest selectedRequest = rideRequests[requestIndex - 1];
                                cout << "Ride request accepted. Pickup: " << selectedRequest.getPickupLocation().getName() << ", Drop-off: " << selectedRequest.getDropoffLocation().getName() << endl;

                                // Simulate ride completion
                                cout << "Ride completed. Please rate your ride (1-5): ";
                                double rating;
                                cin >> rating;
                                driver.addRating(rating);
                                cout << "Thank you for your feedback!" << endl;
                            }
                        }
                    } else if (driverAction == 3) {
                        break;
                    }
                }
            }
        } else if (driverChoice == 2) {
            string name, password, vehicleRegistration, phoneNumber;
            double ratePerKm;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter vehicle registration: ";
            cin >> vehicleRegistration;
            cout << "Enter phone number: ";
            cin >> phoneNumber;
            cout << "Enter rate per km: ";
            cin >> ratePerKm;
            try {
                Driver driver(name, password, vehicleRegistration, phoneNumber, ratePerKm);
                driver.registerDriver();
            } catch (const out_of_range &e) {
                cout << e.what() << endl;
            }
        } else if (driverChoice == 3) {
            break;
        }
    }
}