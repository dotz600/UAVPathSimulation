#include "../include/Point.h"

/// <summary>
/// calculate the distance between 2 points
/// </summary>
/// <param name="p"></param>
/// <returns></returns>
double Point::distance(const Point& p) const {
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

Point Point::operator+(const Point& p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point& p) const {
	return Point(x - p.x, y - p.y);
}

Point Point::operator*(double scalar) const {
	return Point(x * scalar, y * scalar);
}

/// <summary>
/// check if two points are equal according to 2 decimal points
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
bool Point::operator==(const Point& other) const {
	return round(x * 100) == round(other.x * 100)  
		&& round(y * 100) == round(other.y *100);
}

ostream& operator<<(ostream& os, const Point& p) {
	os << '(' << p.x << ',' << p.y << ')';
	return os;
}

istream& operator>>(istream& in, Point& p) {
	char ignore;
	in >> ignore >> p.x >> ignore >> p.y >> ignore;
	return in;
}
