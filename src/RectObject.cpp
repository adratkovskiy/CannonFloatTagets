#include "stdafx.h"
#include "RectObject.h"

RectObject::RectObject(const float scale
    , const IRect& textureRect
    , const FPoint& pos
    , const int health
) :
    _scale(scale)
    , _textureRect(textureRect)
    , _pos(pos)
    , _health(health)
{
    _centerOffset.x = _textureRect.width * _scale / 2;
    _centerOffset.y = _textureRect.height * _scale / 2;
    _size.x = _textureRect.width * _scale;
    _size.y = _textureRect.height * _scale;
    setPosCenter();
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

const FPoint& RectObject::getSize() const
{
    return _size;
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

void RectObject::setPosCenter(const float posCenterX)
{
    _pos.x = posCenterX - _centerOffset.x;
    _posCenter.x = posCenterX;
}

void RectObject::hit()
{
    if (_health > -1)
        _health--;
}

void RectObject::setPosCenter()
{
    _posCenter = _pos + _centerOffset;
}

