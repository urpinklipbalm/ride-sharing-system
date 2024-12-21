cmake_minimum_required(VERSION 3.10)

project(RideSharingSystem)

set(CMAKE_CXX_STANDARD 11)

# Specify the source files
set(SOURCES
    src/main.cpp
    src/User.cpp
    src/Driver.cpp
    src/RideRequest.cpp
    src/Location.cpp
    src/Pricing.cpp
    src/RideQueue.cpp
    src/Rating.cpp
    src/RideHistory.cpp
    src/TrafficUpdates.cpp
)

# Add the executable
add_executable(RideSharingSystem ${SOURCES})