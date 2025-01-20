#pragma once
#include "../include/Point.h"

/// <summary>
/// represent a vector in 2D space
/// </summary>
class Vector : public Point
{
public:
	Vector() : Point() {};
	Vector(double X, double Y) : Point(X,Y) {};
	~Vector() {};

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector normalized();
	

private:
	double magnitude() const;
};

