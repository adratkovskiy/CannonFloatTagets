#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(FPoint pos, float speed, std::vector<float> splinePoints) :
	_centerPos(pos)
	, _speed(speed)
	, _splinePoints(splinePoints)
	, _cannonTimer(0)
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

const float& Cannonball::getCannonTimer() const noexcept
{
	return _cannonTimer;
}

TimedSpline<FPoint>& Cannonball::getSpline()
{
	return _spline;
}

void Cannonball::setShow(bool show)
{
	_show = show;
}

void Cannonball::setCannonTimer(float cannonTimer)
{
	_cannonTimer = cannonTimer;
}

void Cannonball::updPosition(float globalTimer)
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

void Cannonball::splineClear()
{
	_spline.Clear();
}



