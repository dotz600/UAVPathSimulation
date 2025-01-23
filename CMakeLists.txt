cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UAVPathSimulation)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(UAVPathSimulation ${SOURCES})