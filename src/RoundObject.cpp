#include "stdafx.h"
#include "RoundObject.h"

RoundObject::RoundObject(const float scale, const IRect& textureRect, const FPoint& pos):
	_scale(scale)
	, _pos(pos)
{
	_radius = textureRect.width * _scale / 2;
	_textureRect = textureRect;
	setPosCenter();
}

RoundObject& RoundObject::operator=(const RoundObject& obj)
{
	if (this == &obj) {
		return *this;
	}
	_scale = obj._scale;
	_radius = obj._radius;
	_pos = obj._pos;
	_posCenter = obj._posCenter;
	_textureRect = obj._textureRect;
	return *this;
}

RoundObject::~RoundObject()
{
}

bool RoundObject::isCrossing(const FPoint& targetCoord, const float targetRadius)
{
	return (LocalFunctions::pointToPointRange(_pos, targetCoord) <= _radius + targetRadius);
}

const FPoint& RoundObject::getPos() const
{
	return _pos;
}

float RoundObject::getScale() const
{
	return _scale;
}

float RoundObject::getRadius() const
{
	return _radius;
}

const FPoint& RoundObject::getCoordCenter()
{
	return _posCenter;
}

void RoundObject::setPos(const FPoint& pos)
{
	_pos = pos;
	setPosCenter();
}

void RoundObject::addVecToPos(const FPoint& vec)
{
	setPos(_pos + vec);
}

void RoundObject::setPosCenter()
{
	_posCenter = { _pos.x + _radius, _pos.y + _radius };
}
