#include "stdafx.h"
#include "Aim.h"


Aim::Aim(const float scale, const IRect& bitmapRect):
    _scale(scale)
{
    _centerCoord.x = -bitmapRect.width * _scale * 0.5;
    _centerCoord.y = -bitmapRect.height * _scale * 0.5;
}

const float Aim::getScale() const noexcept
{
    return _scale;
}

const FPoint& Aim::getCoordCenter() const noexcept
{
    return _centerCoord;
}
