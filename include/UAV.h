#pragma once
#include "Point.h"
#include "../include/PathStrategy.h"
#include "../include/IFlight.h"

/// <summary>
/// Represents a UAV (Unmanned Aerial Vehicle) that can move in 2D space.
/// This class implements the IFlight interface and uses the Strategy pattern
/// for path calculation.
/// </summary>
class UAV : IFlight
{
public:
	UAV(Point pos, float _angle, float _maxRotateAngle, float _stepSize, PathStrategy* _strategy = nullptr) :
		position(pos), angle(_angle), strategy(_strategy), maxRotateAngle(_maxRotateAngle), stepSize(_stepSize) {};

	~UAV();

	//setters
	void setStrategy(PathStrategy* strategy) { this->strategy = strategy; }
	void setPosition(Point pos) { position = pos; }
	void setAngle(float a) { angle = a; }
	void setMaxAngle(float angle) { maxRotateAngle = angle; }

	//gutters
	const Point& getPosition() const override { return position; }
	const float getAngle() const override { return angle; }
	float getMaxRotateAngle() const override { return maxRotateAngle; }
	float getStepSize() const override { return stepSize; }

	//methods
	std::vector<Point> calculatePath(Point destination);

private:
	Point position; //current position
	float angle; //current angle
	float maxRotateAngle; //max angle that the UAV can rotate
	float stepSize; //max step size for the UAV
	PathStrategy* strategy; //strategy to calculate the path
};
