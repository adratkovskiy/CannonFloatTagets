#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(const float scale
	, const IRect& textureRect
	, const FPoint& pos
	, const float speed
	, const int topBorder
	, const int bottomBorder
	, const int leftBorder
	, const int rightBorder
) : RoundObject(scale, textureRect, pos)
	, _speed(speed)
	, _flightTime(0)
{
	_centerOffset = FPoint({ textureRect.width / 2 * RoundObject::getScale(), textureRect.height / 2 * RoundObject::getScale() });
	_stop = true;
}


bool Cannonball::isStoped() const
{
	return _stop;
}

void Cannonball::setFlightTime(float cannonTimer)
{
	_flightTime = cannonTimer;
}



