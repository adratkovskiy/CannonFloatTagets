#include "stdafx.h"
#include "Button.h"

Button::Button(const FPoint& pos, const float scale, const std::string& text) :
    _pos(pos)
    , _scale(scale)
    , _text(text)
{
}

const float Button::getScale() const noexcept
{
    return _scale;
}

const FPoint& Button::getPos() const noexcept
{
    return _pos;
}

const std::string& Button::getText() const noexcept
{
    return _text;
}


