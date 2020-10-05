#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(const float angle
	, const float scale
	, const FPoint& standPos
	, const FPoint& cannonRotatePoint
	, const FPoint& cannonCenter
) :
	_angle(angle)
	, _scale(scale)
	, _standPos(standPos)
	, _cannonRotatePoint(cannonRotatePoint)
	, _cannonCenter(cannonCenter)
{

}

const float Cannon::getAngle() const noexcept
{
    return _angle;
}

const float Cannon::getScale() const noexcept
{
    return _scale;
}

const FPoint& Cannon::getCannonCenter() const noexcept
{
	return _cannonCenter;
}

const FPoint& Cannon::getCannonRotatePoint() const noexcept
{
	return _cannonRotatePoint;
}

const FPoint& Cannon::getStandPos() const noexcept
{
	return _standPos;
}

void Cannon::setAngle(const float angle)
{
    _angle = angle;
}