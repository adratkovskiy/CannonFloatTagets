#include "stdafx.h"
#include "Functions.h"

float LocalFunctions::pointToPointRange(const FPoint& firstPoint, const FPoint& secondPoint)
{
	return math::sqrt(math::abs(math::sqr(firstPoint.x - secondPoint.x) + math::sqr(firstPoint.y - secondPoint.y)));
}

float LocalFunctions::pointToPointRange(const IPoint& firstPoint, const FPoint& secondPoint)
{
	return pointToPointRange(FPoint(firstPoint), secondPoint);
}

float LocalFunctions::vecLen(const FPoint& vec)
{
	return math::sqrt(math::abs(math::sqr(vec.x) + math::sqr(vec.y)));
}

//опять же, если возвращаю по ссылке, то в void TestWidget::CreateTarget() значение уже умирает
FPoint LocalFunctions::randomVec(const float speed) 
{
	float targetAngle = math::random(math::PI * 2);
	return FPoint({ speed * math::sin(targetAngle), speed * math::cos(targetAngle) });
}
