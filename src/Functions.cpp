#include "stdafx.h"
#include "Functions.h"

const float LocalFunctions::vecLen(const FPoint& firstVec, const FPoint& secondVec)
{
	return math::sqrt(math::abs(math::sqr(firstVec.x - secondVec.x) + math::sqr(firstVec.y - secondVec.y)));
}

const float LocalFunctions::vecLen(const IPoint& firstVec, const FPoint& secondVec)
{
	return math::sqrt(math::abs(math::sqr(firstVec.x - secondVec.x) + math::sqr(firstVec.y - secondVec.y)));
}
