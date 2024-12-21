# Ride-Sharing System

## Overview
This project implements a ride-sharing system that facilitates the management of users and drivers, ride request matching, real-time location tracking, dynamic ride pricing, and more. The system is designed to operate within a simulated city represented as a 100x100 grid.

## Features
- User and Driver Management
- Ride Request Matching
- Real-Time Location Tracking
- Dynamic Ride Pricing
- Ride Request Queue
- Driver Rating System
- User Ride History
- Real-Time Traffic Updates

## Project Structure
```
ride-sharing-system
├── src
│   ├── main.cpp
│   ├── User.cpp
│   ├── User.h
│   ├── Driver.cpp
│   ├── Driver.h
│   ├── RideRequest.cpp
│   ├── RideRequest.h
│   ├── Location.cpp
│   ├── Location.h
│   ├── Pricing.cpp
│   ├── Pricing.h
│   ├── RideQueue.cpp
│   ├── RideQueue.h
│   ├── Rating.cpp
│   ├── Rating.h
│   ├── RideHistory.cpp
│   ├── RideHistory.h
│   ├── TrafficUpdates.cpp
│   ├── TrafficUpdates.h
│   └── CityGrid.txt
├── CMakeLists.txt
└── README.md
```

## Setup Instructions
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Use CMake to configure the project:
   ```
   mkdir build
   cd build
   cmake ..
   ```
4. Build the project:
   ```
   make
   ```
5. Run the application:
   ```
   ./ride-sharing-system
   ```

## Usage
- Users can register and log in to request rides.
- Drivers can log in and accept ride requests.
- The system dynamically calculates ride prices based on various factors.
- Users can view their ride history and rate drivers.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.