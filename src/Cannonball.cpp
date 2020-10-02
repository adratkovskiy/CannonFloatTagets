#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(FPoint pos) : _pos(pos)
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


