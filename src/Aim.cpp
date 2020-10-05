#include "stdafx.h"
#include "Aim.h"


Aim::Aim(const float scale, const IRect& bitmapRect):
    _scale(scale)
    , _bitmapRect(bitmapRect)
{
}

const float Aim::getScale() const noexcept
{
    return _scale;
}
