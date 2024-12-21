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
        cout << "1. User Registration" << endl;
        cout << "2. User Login" << endl;
        cout << "3. Driver Login" << endl;
        cout << "4. Request Ride" << endl;
        cout << "5. Update Traffic Data" << endl;
        cout << "6. Display Traffic Updates" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string userID, name, password;
                cout << "Enter user ID: ";
                cin >> userID;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                user = new User(stoi(userID), name, password);
                user->registerUser();
                break;
            }
            case 2:
                if (user) {
                    user->login();
                } else {
                    cout << "No user registered. Please register first." << endl;
                }
                break;
            case 3: {
                string driverID, name, password;
                cout << "Enter driver ID: ";
                cin >> driverID;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter password: ";
                cin >> password;
                driver = new Driver(stoi(driverID), name, password);
                driver->login(driverID, password);
                break;
            }
            case 4: {
                int id;
                double userLat, userLon, destLat, destLon;
                cout << "Enter request ID: ";
                cin >> id;
                cout << "Enter user latitude: ";
                cin >> userLat;
                cout << "Enter user longitude: ";
                cin >> userLon;
                cout << "Enter destination latitude: ";
                cin >> destLat;
                cout << "Enter destination longitude: ";
                cin >> destLon;
                rideRequest.createRequest(id, userLat, userLon, destLat, destLon);
                rideQueue.addRequest(rideRequest);
                break;
            }
            case 5: {
                string location, status;
                cout << "Enter location: ";
                cin >> location;
                cout << "Enter traffic status: ";
                cin >> status;
                trafficUpdates.updateTrafficData(location, status);
                break;
            }
            case 6:
                trafficUpdates.displayAllTrafficUpdates();
                break;
            case 7:
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