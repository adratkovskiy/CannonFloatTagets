#include "stdafx.h"
#include "RoundObject.h"

RoundObject::RoundObject(const float scale, const IRect& textureRect, const FPoint& pos):
	_scale(scale)
	, _pos(pos)
{
	_radius = textureRect.width * _scale / 2;
}

const bool RoundObject::isCrossing(const FPoint& targetCoord, const float targetRadius)
{
	math::
	return false;
}

const FPoint& RoundObject::getPos() const noexcept
{
	return _pos;
}

const float RoundObject::getScale() const noexcept
{
	return _scale;
}

const float RoundObject::getRadius() const noexcept
{
	return _radius;
}

const FPoint& RoundObject::getCoordCenter() noexcept
{
	return FPoint({ _pos.x + _radius, _pos.y + _radius });
}
