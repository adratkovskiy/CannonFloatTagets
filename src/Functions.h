#pragma once

namespace LocalFunctions
{
	float pointToPointRange(const FPoint& firstPoint, const FPoint& secondPoint);
	float pointToPointRange(const IPoint& firstPoint, const FPoint& secondPoint);
	float vecLen(const FPoint& vec);
	FPoint randomVec(const float speed);
}
