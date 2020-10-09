#include "stdafx.h"
#include "RoundObject.h"

RoundObject::RoundObject(const float scale, const IRect& textureRect, FPoint& centerPos, targetType type):
	_scale(scale)
	, _centerPos(centerPos)
	, _type(type)
{
	_radius = textureRect.width * _scale;
}

const RoundObject::targetType& RoundObject::getType() const noexcept
{
	return _type;
}

const FPoint& RoundObject::getPos() const noexcept
{
	return _centerPos;
}

const float RoundObject::getScale() const noexcept
{
	return _scale;
}
