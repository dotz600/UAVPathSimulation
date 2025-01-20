#pragma once
#include <vector>
#include "../include/Point.h"
#include "../include/Vector.h"
#include "../include/IFlight.h"

/// <summary>
/// abstract class for path calculation strategy
/// </summary>
class PathStrategy
{
public:
	PathStrategy()  = default;
	virtual ~PathStrategy() = default;

	virtual std::vector<Point> calculate(const IFlight* context, const Point& destination) const = 0;

private:

};

