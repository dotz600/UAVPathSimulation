#include "../include/UAV.h"

// Destructor
UAV::~UAV() {
    if (strategy != nullptr) {
        delete strategy;
        strategy = nullptr;
    }
}

// Calculate the path to the destination
std::vector<Point> UAV::calculatePath(Point destination) {
    if (!strategy) {
        throw std::runtime_error("No path strategy set");
    }
    return strategy->calculate(this, destination);
}
