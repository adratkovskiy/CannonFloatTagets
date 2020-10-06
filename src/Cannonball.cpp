#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(const FPoint& pos, float speed, const std::vector<float>& splinePoints) :
	_centerPos(pos)
	, _speed(speed)
	, _splinePoints(std::move(splinePoints))
	, _flightTime(0)
{
}

const FPoint& Cannonball::getPosition() const noexcept
{
	return _currentPosition;
}

const bool& Cannonball::getShow() const noexcept
{
	return _show;
}

const float& Cannonball::getSpeed() const noexcept
{
	return _speed;
}

const float& Cannonball::getFlightTime() const noexcept
{
	return _flightTime;
}

TimedSpline<FPoint>& Cannonball::getSpline()
{
	return _spline;
}

void Cannonball::setShow(bool show)
{
	_show = show;
}

void Cannonball::setFlightTime(float cannonTimer)
{
	_flightTime = cannonTimer;
}

void Cannonball::updPosition(const float globalTimer)
{
	_currentPosition = _spline.getGlobalFrame(math::clamp(0.0f, 1.0f, globalTimer / 6.0f)) + _centerPos;
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

void Cannonball::splineClear() noexcept
{
	_spline.Clear();
}



