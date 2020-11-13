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

float Cannon::getAngle() const
{
    return _angle;
}

float Cannon::getScale() const
{
    return _scale;
}

const FPoint& Cannon::getCannonCenter() const
{
	return _cannonCenter;
}

const FPoint& Cannon::getCannonRotatePoint() const
{
	return _cannonRotatePoint;
}

const FPoint& Cannon::getStandPos() const
{
	return _standPos;
}

void Cannon::setAngle(const float angle)
{
    _angle = angle;
}