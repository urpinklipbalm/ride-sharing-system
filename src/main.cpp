#include <iostream>
#include "User.h"
#include "Driver.h"
#include "RideRequest.h"
#include "Location.h"
#include "Pricing.h"
#include "RideQueue.h"
#include "Rating.h"
#include "RideHistory.h"
#include "TrafficUpdates.h"

using namespace std;

int main() {
    cout << "Welcome to the Ride-Sharing System!" << endl;

    RideRequest rideRequest;
    Location location;
    Pricing pricing;
    RideQueue rideQueue;
    RideHistory rideHistory;
    TrafficUpdates trafficUpdates;

    User* user = nullptr;
    Driver* driver = nullptr;

    while (true) {
        cout << "Please choose an option: " << endl;
        cout << "1. User Login" << endl;
        cout << "2. Driver Login" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string userID, password;
                cout << "Enter userID: ";
                cin >> userID;
                cout << "Enter password: ";
                cin >> password;
                user = new User("", "", "");
                if (user->login(userID, password)) {
                    while (true) {
                        cout << "Please choose an option: " << endl;
                        cout << "1. Request Ride" << endl;
                        cout << "2. View Ride History" << endl;
                        cout << "3. Log Out" << endl;

                        int userChoice;
                        cin >> userChoice;

                        if (userChoice == 1) {
                            double destLat, destLon;
                            cout << "Enter destination latitude: ";
                            cin >> destLat;
                            cout << "Enter destination longitude: ";
                            cin >> destLon;
                            user->requestRide(destLat, destLon);
                            cout << "Choose payment method: " << endl;
                            cout << "1. In-app Payment" << endl;
                            cout << "2. Cash Payment" << endl;

                            int paymentChoice;
                            cin >> paymentChoice;

                            if (paymentChoice == 1) {
                                double amount = pricing.calculatePrice(user->getLocation().first, user->getLocation().second, destLat, destLon, driver->getRatePerKm());
                                driver->processPayment(amount);
                            } else {
                                cout << "Pay cash to the driver." << endl;
                            }
                        } else if (userChoice == 2) {
                            vector<pair<int, string>> history = user->getRideHistory();
                            for (const auto& ride : history) {
                                cout << "Ride ID: " << ride.first << ", Status: " << ride.second << endl;
                            }
                        } else if (userChoice == 3) {
                            delete user;
                            user = nullptr;
                            break;
                        } else {
                            cout << "Invalid option. Please try again." << endl;
                        }
                    }
                }
                break;
            }
            case 2: {
                string driverID, password;
                cout << "Enter driverID: ";
                cin >> driverID;
                cout << "Enter password: ";
                cin >> password;
                driver = new Driver("", "", "", "", 0.0);
                if (driver->login(driverID, password)) {
                    while (true) {
                        cout << "Please choose an option: " << endl;
                        cout << "1. Turn Availability On" << endl;
                        cout << "2. Receive Ride Requests" << endl;
                        cout << "3. Log Out" << endl;

                        int driverChoice;
                        cin >> driverChoice;

                        if (driverChoice == 1) {
                            driver->setAvailability(true);
                            cout << "Availability turned on." << endl;
                        } else if (driverChoice == 2) {
                            if (!rideQueue.isEmpty()) {
                                auto rideRequest = rideQueue.getNextRequest();
                                if (driver->acceptRide(rideRequest.getID(), rideRequest.getUserLatitude(), rideRequest.getUserLongitude())) {
                                    driver->completeRide(rideRequest.getID());
                                }
                            } else {
                                cout << "No ride requests available." << endl;
                            }
                        } else if (driverChoice == 3) {
                            delete driver;
                            driver = nullptr;
                            break;
                        } else {
                            cout << "Invalid option. Please try again." << endl;
                        }
                    }
                }
                break;
            }
            case 3:
                cout << "Exiting the system." << endl;
                delete user;
                delete driver;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}