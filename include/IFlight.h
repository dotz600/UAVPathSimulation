#pragma once
#include "../include/Point.h"
#include "../include/Vector.h"

/// <summary>
/// interface for the flight
/// give methods to get the position, angle, max rotate angle and step size
/// </summary>
class  IFlight
{
public:

	virtual ~IFlight() = default;

	virtual const Point& getPosition() const = 0;

	virtual const float getAngle() const = 0;

	virtual float getMaxRotateAngle() const = 0;

	virtual float getStepSize() const = 0;
};

