#include "../include/Vector.h"
#include <math.h>

/// <summary>
/// normalize the vector
/// </summary>
/// <returns></returns>
Vector Vector::normalized() {
	double mag = magnitude();

	if (mag > 0) {
		x /= mag;
		y /= mag;
		return Vector(x, y);
	}
	return *this;
}

/// <summary>
/// calculate the magnitude of the vector
/// </summary>
/// <returns></returns>
double Vector::magnitude() const {
	return sqrt(x * x + y * y);
}

Vector Vector::operator+(const Vector& v) const {
	return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const {
	return Vector(x - v.x, y - v.y);
}

