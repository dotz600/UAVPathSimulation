cmake_minimum_required(VERSION 3.10)
project(UAVPathSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(uav_simulation ${SOURCES})
