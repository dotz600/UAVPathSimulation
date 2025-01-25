#pragma once
#include <cmath>
#include <ostream>
#include <istream>
using namespace std;

/// <summary>
/// represents a point in 2D space
/// </summary>
class Point
{
public:
	
	Point() : x(0), y(0) {};
	Point(double X, double Y) : x(X), y(Y) {};
	Point(const Point& other) : x(other.x), y(other.y) {}
	~Point() = default;

	//methods 
	double distance(const Point& p) const;

	//operators
	Point operator+(const Point& p) const;
	Point operator-(const Point& p) const;
	Point operator*(double scalar) const;
	friend ostream& operator<<(ostream& os, const Point& p);
	friend istream& operator>>(istream& in, Point& p);
	bool operator==(const Point& other) const;

	//getters
	double getX() const { return x; }
	double getY() const { return y; }

protected:
	double x;
	double y;
};

