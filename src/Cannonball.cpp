#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(const float scale
	, const IRect& textureRect
	, const FPoint& pos
	, const float speed
	, const std::vector<float>& splinePoints
) : RoundObject(scale, textureRect, pos)
	, _speed(speed)
	, _splinePoints(std::move(splinePoints))
	, _flightTime(0)
{
	_centerOffset = FPoint({ textureRect.width / 2 * RoundObject::getScale(), textureRect.height / 2 * RoundObject::getScale() });
	_stop = true;
}

float Cannonball::getSpeed() const
{
	return _speed;
}

float Cannonball::getFlightTime() const
{
	return _flightTime;
}

TimedSpline<FPoint>& Cannonball::getSpline()
{
	return _spline;
}

bool Cannonball::isStoped() const
{
	return _stop;
}

void Cannonball::setFlightTime(float cannonTimer)
{
	_flightTime = cannonTimer;
}

void Cannonball::updPosition(const float globalTimer)
{
	RoundObject::setPos(_spline.getGlobalFrame(math::clamp(0.0f, 1.0f, globalTimer / 6.0f)) - _centerOffset);
}

void Cannonball::setSpline(FPoint cannonCenter, FPoint mousePos)
{
	_spline.addKey(_splinePoints[0], cannonCenter);
	_spline.addKey(_splinePoints[1], mousePos);
	_spline.addKey(_splinePoints[2], { (float)(mousePos.x + (mousePos.x - cannonCenter.x)), (float)(mousePos.y + 0.3 * (mousePos.y - cannonCenter.y)) });
	_spline.addKey(_splinePoints[3], { (float)(mousePos.x + 2 * (mousePos.x - cannonCenter.x)), (float)(mousePos.y) });
	_spline.addKey(_splinePoints[4], { (float)(cannonCenter.x + 1.75 * (mousePos.x + (mousePos.x - cannonCenter.x) - cannonCenter.x)), (float)(-30) });
	_spline.CalculateGradient();
}

void Cannonball::splineClear()
{
	_spline.Clear();
}



