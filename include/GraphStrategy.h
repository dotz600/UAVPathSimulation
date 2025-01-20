#pragma once
#include "../include/PathStrategy.h"
#include <queue>

/// <summary>
/// contain the logic for the path calculation using the graph search algorithm.
/// The algorithm base on the A* algorithm and GBFS to find the path,
/// and can find the optimal path for thus who want to wait a bit longer
/// contain a Node struct that represent a point in the graph, 
/// and private helper functions for the calculation
/// </summary>
class GraphStrategy : public PathStrategy
{
public:
	GraphStrategy() = default;
	~GraphStrategy() = default;

	std::vector<Point> calculate(const IFlight* context, const Point& destination) const override;

	struct Node {

		Point position;
		float angle; // (1,0) vector is 0
		double gCost;// Cost from start
		double hCost;// Heuristic cost to target
		double fCost;// Total cost (g + h)
		Node* parent;

		bool operator==(const Node& other) const;
		Node(Point pos, float dir, double g, double h, Node* par = nullptr);
		Node(Point pos, float dir, double h);
	};

	struct NodePtrCompare {
		bool operator()(const Node* a, const Node* b) const;
	};

private:
	// delete all nodes in the openSet and thus who have been popped
	void cleanupNodes(std::priority_queue<Node*, std::vector<Node*>, NodePtrCompare>& openSet, std::vector<Node*>& popsNode) const;
	
	// reconstruct the path from the target node to the start
	std::vector<Point> reconstructPath(Node* cur, Point target) const;
	
	// generate all the neighbors of the current node
	std::vector<Node*> generateNeighbors(float maxAngle, Node* cur, float stepSize, const Point& destination) const;
	
	// create a new node with the given parameters
	Node* createNeighbor(int i, float maxAngle, Node* cur, float stepSize, const Point& destination) const;

	// normalize the angle to be in the range of [0, 360.0)
	template <typename T>
	void normalizeAngle(T& newAngle) const;

	// move the point in the given direction
	Point moveInDirection(const Point& pos, float angle, float stepSize) const;
	
	// calculate the heuristic cost from the current position to the target position
	// using the Euclidean distance
	double heuristic(const Point& pos, const Point& tar, float stepSize) const;
	
	// calculate the heuristic cost with given angle weight
	double angleHeuristic(const Point& currentPos, double currentAngle, const Point& targetPos, double angleWeight) const;
	
	// calculate the difference between two angles
	double angleDifference(double angle1, double angle2) const;

	//calculate the angle to the target position
	double angleToTarget(const Point& cur, const Point& target) const;
};


