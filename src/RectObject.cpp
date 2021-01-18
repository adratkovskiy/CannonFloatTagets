#include "stdafx.h"
#include "RectObject.h"

RectObject::RectObject(const float scale
    , const IRect& textureRect
    , const FPoint& pos
) :
    _scale(scale)
    , _textureRect(textureRect)
    , _pos(pos)
{
    _centerOffset.x = _textureRect.width * _scale / 2;
    _centerOffset.y = _textureRect.height * _scale / 2;
}

RectObject::~RectObject()
{
}

float RectObject::getScale() const
{
    return _scale;
}

const FPoint& RectObject::getPos() const
{
    return _pos;
}

const FPoint& RectObject::getCoordCenter() const
{
    return _posCenter;
}

void RectObject::setPos(const FPoint& pos)
{
    _pos = pos;
    setPosCenter();
}

void RectObject::setPosCenter(const FPoint& pos)
{
    _pos = pos - _centerOffset;
    _posCenter = pos;
}

void RectObject::setPosCenter(const float posCenter)
{
    _pos.x = posCenter - _centerOffset.x;
    _posCenter.x = posCenter;
}

void RectObject::setPosCenter()
{
    _posCenter = _pos + _centerOffset;
}

