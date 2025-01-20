#include "../include/GraphStrategy.h"
#include <queue>
#include <unordered_map>
#include "../include/HashFunctions.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const float DEGREE = 360.0;

#pragma region Path Calculation
/// <summary>
/// calculate the path from the current position to the destination
/// according to combination of A* and GBFS algorithm
/// </summary>
/// <param name="context"></param>
/// <param name="destination"></param>
/// <returns> std::vector<Point> </returns>
std::vector<Point> GraphStrategy::calculate(const IFlight* context, const Point& destination) const {
	//extract data
	const Point& position = context->getPosition();
	const float curAngel = context->getAngle();
	float maxAngle = context->getMaxRotateAngle();
	float stepSize = context->getStepSize();

	//queue to mange nodes using node pointer compare to define the priority according to minHeap
	std::priority_queue<Node*, std::vector<Node*>, NodePtrCompare> queue;
	// visitedNodes keeps track of which nodes have been added to the queue to avoid duplicates.
	std::unordered_map<GraphStrategy::Node, bool> visitedNodes;
	//track the nodes that have been popped
	std::vector<Node*> popsNode;

	//define the start node
	Node* cur = new Node(position, curAngel, 0, position.distance(destination));
	queue.push(cur);
	visitedNodes[*cur] = true;

	while (!queue.empty()) {

		cur = queue.top();
		queue.pop();
		popsNode.push_back(cur);
		visitedNodes[*cur] = false;

		// Goal check
		if (cur->position.distance(destination) < stepSize) {
			float targetAngle = angleToTarget(cur->position, destination);
			normalizeAngle(targetAngle);
			//check its in the same direction
			if (angleDifference(cur->angle, targetAngle) < maxAngle) {
				std::vector<Point> path = reconstructPath(cur, destination);
				cleanupNodes(queue, popsNode);
				return path;
			}
		}

		std::vector<Node*> neighbors =
			generateNeighbors(maxAngle, cur, stepSize, destination);

		for (Node* neighbor : neighbors) {
			//define neighbor costs
			double newG = cur->gCost + 1.0;// Adding 1 as the cost of traveling from v to g
			neighbor->gCost = newG;
			neighbor->fCost = neighbor->hCost; // Add gCost for optimal path
			neighbor->parent = cur;

			if (!visitedNodes[*neighbor]) { // Not in openSet
				queue.push(neighbor);
				visitedNodes[*neighbor] = true;
			}
		}
	}
	//if no path found
	cleanupNodes(queue, popsNode);
	return {};
}

/// <summary>
/// go back from the target node to the start node
/// and store the path to target
/// </summary>
/// <param name="cur"></param>
/// <param name="target"></param>
/// <returns></returns>
std::vector<Point> GraphStrategy::reconstructPath(Node* cur, Point target) const {
	std::vector<Point> path;
	path.push_back(target);
	while (cur != nullptr) {
		path.push_back(cur->position);
		cur = cur->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}

/// <summary>
/// delete all nodes in the openSet and thus who have been popped
/// </summary>
/// <param name="openSet"></param>
/// <param name="popsNode"></param>
void GraphStrategy::cleanupNodes(std::priority_queue<GraphStrategy::Node*, std::vector<GraphStrategy::Node*>, GraphStrategy::NodePtrCompare>& openSet, std::vector<GraphStrategy::Node*>& popsNode) const {
	while (!openSet.empty()) {
		auto nd = openSet.top();
		openSet.pop();
		delete nd;
	}
	for (Node* nd : popsNode) {
		delete nd;
	}
}

#pragma endregion

#pragma region Node Generation
/// <summary>
/// generate the neighbors of the current node
/// </summary>
/// <param name="q1"></param>
/// <param name="maxAngle"></param>
/// <param name="cur"></param>
/// <param name="stepSize"></param>
/// <param name="destination"></param>
/// <returns>std::vector<Node*> </returns>
std::vector<GraphStrategy::Node*> GraphStrategy::generateNeighbors(float maxAngle, Node* cur, float stepSize, const Point& destination) const {
	std::vector<Node*> res;
	int maxAngInt = (int)maxAngle;
	for (int i = -maxAngInt; i <= maxAngInt; i++) {
		Node* nd = createNeighbor(i, maxAngle, cur, stepSize, destination);
		res.push_back(nd);
	}
	return res;
}

/// <summary>
/// create the neighbor node with the given parameters
/// </summary>
/// <param name="i"></param>
/// <param name="maxRotateAngle"></param>
/// <param name="cur"></param>
/// <param name="stepSize"></param>
/// <param name="destination"></param>
/// <returns></returns>
GraphStrategy::Node* GraphStrategy::createNeighbor(int angleOffset, float maxRotateAngle, Node* cur, float stepSize, const Point& destination) const {

	float newAngle = cur->angle + angleOffset;

	normalizeAngle(newAngle);

	Point newPos = moveInDirection(cur->position, newAngle, stepSize);

	// Choose heuristic
	double h = angleHeuristic(newPos, newAngle, destination, 0.1);
	//double h1 = heuristic(newPos, destination, stepSize);
	return new Node(newPos, newAngle, h);
}
#pragma endregion

#pragma region Heuristic Functions
/// <summary>
/// heuristic function to calculate the cost from the current position to target
/// according to the Euclidean distance
/// </summary>
/// <param name="pos"></param>
/// <param name="tar"></param>
/// <param name="stepSize"></param>
/// <returns></returns>
double GraphStrategy::heuristic(const Point& pos, const Point& tar, float stepSize) const {
	return pos.distance(tar) / (double)stepSize;
}


/// <summary>
/// heuristic function number 2 to calculate cost with angel weight
/// give minimal h cost to the node that has the same direction as the target
/// or that have the less deference with the target direction
/// </summary>
/// <param name="currentPos"></param>
/// <param name="currentAngle"></param>
/// <param name="targetPos"></param>
/// <param name="angleWeight"></param>
/// <returns></returns>
double GraphStrategy::angleHeuristic(const Point& cur, double currentAngle, const Point& target, double angleWeight) const {

	double distance = cur.distance(target);

	double desiredAngle = angleToTarget(cur, target);
	normalizeAngle(desiredAngle);


	double angleDiff = angleDifference(currentAngle, desiredAngle);

	return distance + angleWeight * angleDiff;
}
#pragma endregion

#pragma region Angle Calculation & movement
/// <summary>
/// return the deference between two angles
/// </summary>
/// <param name="angle1"></param>
/// <param name="angle2"></param>
/// <returns></returns>
double GraphStrategy::angleDifference(double angle1, double angle2) const {
	double diff = std::fabs(angle1 - angle2);
	return std::fmin(diff, DEGREE - diff);  // Smallest angle difference
}

/// <summary>
/// calculate the angle to the target position
/// </summary>
/// <param name="cur"></param>
/// <param name="target"></param>
/// <returns></returns>
double GraphStrategy::angleToTarget(const Point& cur, const Point& target) const {
	return std::atan2(target.getY() - cur.getY(), target.getX() - cur.getX()) * (180.0 / M_PI);
}

/// <summary>
/// normalize the angle to be in the range of [0, 360.0)
/// </summary>
/// <type Param name="T"></type Param>
/// <param name="newAngle"></param>
template <typename T>
void GraphStrategy::normalizeAngle(T& newAngle) const {
	// Keep the angle within the range [0, 360)
	if (newAngle >= DEGREE) newAngle -= DEGREE;
	if (newAngle < 0.0) newAngle += DEGREE;
}

/// <summary>
/// move point in the given direction
/// </summary>
/// <param name="pos"></param>
/// <param name="angle"></param>
/// <param name="stepSize"></param>
/// <returns></returns>
Point GraphStrategy::moveInDirection(const Point& pos, float angle, float stepSize) const {
	double radians = angle * M_PI / 180.0;  // Convert to radians
	double dx = std::cos(radians) * stepSize;
	double dy = std::sin(radians) * stepSize;
	return Point(pos.getX() + dx, pos.getY() + dy);
}

#pragma endregion

#pragma region Node Implementation
GraphStrategy::Node::Node(Point pos, float dir, double g, double h, Node* par)
	: position(pos), angle(dir), gCost(g), hCost(h), fCost(g + h), parent(par) {}

GraphStrategy::Node::Node(Point pos, float dir, double h)
	: position(pos), angle(dir), gCost(std::numeric_limits<double>::max()),
	hCost(h), fCost(std::numeric_limits<double>::max()),
	parent(nullptr) {}


bool GraphStrategy::Node::operator==(const Node& other) const {
	return position == other.position && round(angle * 100) == round(other.angle * 100);
}

bool GraphStrategy::NodePtrCompare::operator()(const Node* a, const Node* b) const {
	return a->fCost > b->fCost;  // Min-heap
}

#pragma endregion