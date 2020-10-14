#include "stdafx.h"
#include "Functions.h"

const float LocalFunctions::pointToPointRange(const FPoint& firstPoint, const FPoint& secondPoint)
{
	return math::sqrt(math::abs(math::sqr(firstPoint.x - secondPoint.x) + math::sqr(firstPoint.y - secondPoint.y)));
}

const float LocalFunctions::pointToPointRange(const IPoint& firstPoint, const FPoint& secondPoint)
{
	return pointToPointRange(FPoint(firstPoint), secondPoint);
	//FPoint(firstPoint);
	//return math::sqrt(math::abs(math::sqr(firstPoint.x - secondPoint.x) + math::sqr(firstPoint.y - secondPoint.y)));
}
