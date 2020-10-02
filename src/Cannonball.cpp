#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(FPoint pos, float speed) : 
	_pos(pos)
	, _speed(speed)
	, _cannonTimer(0)
{
}

const FPoint& Cannonball::getPos() const noexcept
{
	return _pos;
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

void Cannonball::setShow(bool show)
{
	_show = show;
}

void Cannonball::setCannonTimer(float cannonTimer)
{
	_cannonTimer = cannonTimer;
}


