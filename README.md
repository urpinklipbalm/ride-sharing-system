# Ride-Sharing System
This project uses various data structures and algorithms to implement a comprehensive ride-sharing system. Key concepts include Bloom filters for quick existence checks, priority queues for managing driver ratings, graph algorithms for route optimization, and file I/O for persistent data storage. The system is designed to handle user and driver interactions, ride requests, dynamic pricing, and more.

## Overview

The Ride-Sharing System is designed to facilitate the management of users and drivers, ride request matching, real-time location tracking, dynamic ride pricing, and more. The system operates within a simulated city represented as a 100x100 grid.

## Key Concepts and Data Structures

### 1. Bloom Filters
- **Usage**: Quickly check the existence of an element, such as checking if a driver ID exists or if a driver is available, with a small probability of false positives.
- **Implementation**: Implemented in `src/bloom_filter/BloomFilter.cpp` and `src/bloom_filter/BloomFilter.h`.
- **Example**: Used to load driver availability and check if a driver is available.

### 2. Priority Queues (Heaps)
- **Usage**: Efficiently manage priority queues, such as finding the nearest available driver or handling ride requests based on priority.
- **Implementation**: Implemented in `src/data structures/PriorityQueue.h`.
- **Example**: Used to sort drivers by rating when a user requests a ride.

### 3. Graph Algorithms for Route Optimization
- **Usage**: Find the shortest or fastest route between locations using Dijkstra's algorithm.
- **Implementation**: Implemented in `src/graph/Graph.cpp` and `src/graph/Graph.h`.
- **Example**: Used to find the shortest path between pickup and drop-off locations.

### 4. File I/O
- **Usage**: Save and load user, driver, and ride data.
- **Implementation**: Various classes such as `User`, `Driver`, and `RideRequest` use file I/O to persist data.
- **Example**: User and driver data are saved and loaded from files.

### 5. Input Validation
- **Usage**: Ensure user input is within a valid range.
- **Implementation**: Implemented in `src/utils/Utils.cpp` and `src/utils/Utils.h`.
- **Example**: Used to get validated input from the user within a specified range.

### 6. Dynamic Pricing
- **Usage**: Calculate ride prices based on various factors such as distance, time of day, surge pricing, and traffic conditions.
- **Implementation**: Implemented in `src/pricing/Pricing.cpp` and `src/pricing/Pricing.h`.
- **Example**: Used to calculate the fare for a ride.

### 7. Traffic Updates
- **Usage**: Manage and display traffic updates for different locations.
- **Implementation**: Implemented in `src/TrafficUpdates.cpp` and `src/TrafficUpdates.h`.
- **Example**: Used to update and retrieve traffic status for locations.

## Running the Project

1. **Ensure all dependencies are installed**: Make sure you have a C++ compiler installed (e.g., `g++`).

2. **Compile the project**: Navigate to the project directory and compile the source files. You can use the following command in the terminal:
   ```sh
   g++ -o RideSharingSystem src/*.cpp src/user/*.cpp src/driver/*.cpp src/location/*.cpp src/utils/*.cpp src/rides/*.cpp src/graph/*.cpp src/data\ structures/*.cpp src/bloom_filter/*.cpp src/pricing/*.cpp src/rating/*.cpp src/TrafficUpdates.cpp
   then run the executable:
   ./RideSharingSystem