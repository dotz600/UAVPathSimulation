#  UAV Pathfinding Simulation

## Overview

This project uses advanced pathfinding algorithms to simulate a UAV (Unmanned Aerial Vehicle) navigating in a 2D space. The core functionality is built around modular, object-oriented design principles, allowing flexible configuration and extension.

The UAV leverages algorithms like A\* and Greedy Best-First Search (GBFS) to calculate optimal or near-optimal paths to a given destination, considering movement constraints such as angle limits and step sizes. The system is designed to be efficient, maintainable, and easily extensible for future enhancements.

---

## Features

- **Pathfinding Algorithms:** Implements A\* and GBFS algorithms for efficient path calculations.
- **Customizable Path Strategy:** Modular design allows easy swapping of pathfinding strategies.
- **2D Space Navigation:** Supports UAV movement simulation with configurable step size and rotation constraints.
- **Reusable Components:** Includes generic utilities.
- **Comprehensive Error Handling:** Handles invalid states gracefully to prevent crashes.
- **Real-time visualization of UAV movement:** Introduce a Python script to execute the C++ program and simulate the UAV's path in a graphical view.

---

## Architecture

### Key Classes

1. **Point**

   - Represents a point in 2D space.
   - Provides basic operations like addition, subtraction, and scalar multiplication.
   - Calculates the distance between points.

2. **Vector**

   - Inherits from `Point` to represent 2D vectors.
   - Adds functionality for normalization and magnitude calculation.

3. **PathStrategy (Interface)**

   - Abstract interface for pathfinding strategies.
   - Allows the use of different algorithms for path calculation.
     

4. **GraphStrategy**

   - Implements pathfinding logic (PathStrategy Interface) using A\* and GBFS algorithms.
   - Defines private helper methods for heuristic calculations, neighbor generation, and path reconstruction.

5. **UAV**

   - Represents a UAV navigating in 2D space.
   - Encapsulates key properties:
     - **Position:** Current location in 2D space.
     - **Angle:** Current direction of movement.
     - **Movement Constraints:** Includes maximum rotation angle and fixed step size.
   - Delegates path calculation to a configurable `PathStrategy`, enabling flexibility in choosing algorithms.


6. **IFlight (Interface)**

   - Defines UAV-related properties for path calculation.
   - Ensures a standardized interface for interacting with pathfinding algorithms.

---

## Prerequisites

- **Compiler:** Requires a C++ compiler and Python interpreter for the simulation view.

---

## Getting Started

### 1. Clone the Repository

```bash
git clone <repository-url>
cd <repository-folder>
```

### 2. Build the Project

Use your preferred build system (e.g., `cmake` or a simple `Makefile`). Below is an example for g++:

```bash
g++ -std=c++17 -o uav_simulation src/*.cpp
```

### 3. Run the Simulation

```bash
./uav_simulation
```

---

## Usage

1. **Initialize a UAV:**
   In the /resources/inputData.txt file, change the start point, destination point, current angle, max rotate angle, and step size and save the file.
   

2. **Simulate Movement:**
   Run to view the result.
   ```
   py /pathPrinter.py

## Example Output

The Python script executes the cpp program that calculates the path and then simulates the path according to /pathOutput.txt as the UAV's calculated path, displayed as a series of points, e.g.:
```
Calculated Path:
(0,0)
(1,1)
(2,2)
...
(10,10)


```

---

## Extensibility

1. **Add New Pathfinding Algorithms:**

   - Derive a new class from `PathStrategy`.
   - Implement the `calculate` method to define custom logic.

2. **Enhance UAV Behavior:**

   - Extend the `UAV` class to include additional capabilities like obstacle avoidance or 3D movement.


