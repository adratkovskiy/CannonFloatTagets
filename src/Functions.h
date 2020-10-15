#pragma once

namespace LocalFunctions
{
	const float pointToPointRange(const FPoint& firstPoint, const FPoint& secondPoint);
	const float pointToPointRange(const IPoint& firstPoint, const FPoint& secondPoint);
	const float vecLen(const FPoint& vec);
	FPoint& randomVec(const float speed);
}
