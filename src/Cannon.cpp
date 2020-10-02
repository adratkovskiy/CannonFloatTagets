#include "stdafx.h"
#include "Cannon.h"

Cannon::Cannon(float angle
	, float scale
	, FPoint standPos
	, FPoint cannonRotatePoint
	, FPoint cannonCenter
) :
	_angle(angle)
	, _scale(scale)
	, _standPos(standPos)
	, _cannonRotatePoint(cannonRotatePoint)
	, _cannonCenter(cannonCenter)
{

}

float& Cannon::getAngle()
{
    return _angle;
}

float& Cannon::getScale()
{
    return _scale;
}

FPoint& Cannon::getCannonCenter()
{
	return _cannonCenter;
}

FPoint& Cannon::getCannonRotatePoint()
{
	return _cannonRotatePoint;
}

FPoint& Cannon::getStandPos()
{
	return _standPos;
}

void Cannon::setAngle(float angle)
{
    _angle = angle;
}