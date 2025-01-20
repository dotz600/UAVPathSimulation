#include <iostream>
#include <fstream>
#include "../include/UAV.h"
#include "../include/GraphStrategy.h"
using namespace std;

struct InputData {
    Point position;
    Point target;
    float curAngle = 0;
    float maxAngle = 0;
    float stepSize = 0;
};

InputData readInputData(const char* filename);
void writePath(const char* filename, const std::vector<Point>& path);


int main() {
    try {
        constexpr const char* inputFile = "resources/inputData.txt";
        constexpr const char* outputFile = "resources/pathOutput.txt";

        InputData data = readInputData(inputFile);

        // Create UAV and calculate path
        UAV uav(data.position, data.curAngle, data.maxAngle,
            data.stepSize, new GraphStrategy());
        std::vector<Point> path = uav.calculatePath(data.target);

        // Write results
        writePath(outputFile, path);

        std::cout << "Path calculation completed successfully. Output saved to: "
            << outputFile << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

// Function to read input data from file
InputData readInputData(const char* filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open input file: " + std::string(filename));
    }

    InputData data;
    if (!(inFile >> data.position >> data.target >>
        data.curAngle >> data.maxAngle >> data.stepSize)) {
        throw std::runtime_error("Invalid input file format");
    }

    inFile.close();
    return data;
}

// Function to write path to output file
void writePath(const char* filename, const std::vector<Point>& path) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open output file: " + std::string(filename));
    }

    for (const auto& point : path) {
        outFile << point << endl;
    }

    outFile.close();
}
