#pragma once
#include "../include/GraphStrategy.h"
#include <functional>
#include <cmath>
#include <limits>

/// <summary>
/// override hash function for Point, Vector and Node
/// so that they can be used as keys in unordered_map or set
/// </summary>
namespace std {
	//hash Point according to 2 digits after the decimal point
	//so that two points with the same coordinates are considered equal
	template <>
	struct hash<Point> {
		size_t operator()(const Point& p) const {
			return std::hash<double>()(round(p.getX() * 100)) ^ std::hash<double>()(round(p.getY() * 100));
		}
	};

	template <>
	struct hash<Vector> {
		size_t operator()(const Vector& v) const {
			return std::hash<double>()(v.getX()) ^ std::hash<double>()(v.getY());
		}
	};

	//hash node according to position and angle
	//angle is rounded to 2 digits after the decimal point
	template <>
	struct hash<GraphStrategy::Node> {
		size_t operator()(const GraphStrategy::Node& n) const {
			size_t h1 = std::hash<Point>()(n.position);
			size_t h2 = std::hash<float>()(round(n.angle * 100));
			return h1 ^ h2;
		}
	};
}



