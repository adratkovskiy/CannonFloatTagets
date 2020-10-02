#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(FPoint pos) : _pos(pos)
{
}

const FPoint& Cannonball::getPos()
{
	return _pos;
}

bool& Cannonball::getShow()
{
	return _show;
}


