#include "stdafx.h"
#include "RoundObject.h"

RoundObject::RoundObject(const float scale, const IRect& textureRect, const FPoint& pos):
	_scale(scale)
	, _pos(pos)
{
	_radius = textureRect.width * _scale / 2;
	setPosCenter();
}

const bool RoundObject::isCrossing(const FPoint& targetCoord, const float targetRadius)
{
	return (LocalFunctions::pointToPointRange(_pos, targetCoord) <= _radius + targetRadius);
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
	return _posCenter;
}

void RoundObject::setPos(FPoint& pos)
{
	_pos = pos;
	setPosCenter();
}

void RoundObject::addVecToPos(FPoint& vec)
{
	setPos(_pos += vec);
}

void RoundObject::setPosCenter()
{
	_posCenter = { _pos.x + _radius, _pos.y + _radius };
}
