#include "stdafx.h"
#include "Button.h"

Button::Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect) :
    _pos(pos)
    , _scale(scale)
    , _text(text)
    , _pressed(false)
{
    _size.x = textureRect.width * _scale;
    _size.y = textureRect.height * _scale;
    _textPos = pos + _size / 2;
}

const bool Button::click(const IPoint& mouse_pos)
{
    if ((mouse_pos.x >= _pos.x)
        & (mouse_pos.x <= _pos.x + _size.x)
        & (mouse_pos.y >= _pos.y)
        & (mouse_pos.y <= _pos.y + _size.y)
        ) {
        _pressed = true;
    }
    return _pressed;
}

void Button::noPressed() noexcept
{
    _pressed = false;
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

const FPoint& Button::getTextPos() const noexcept
{
    return _textPos;
}

const bool Button::getPressed() const noexcept
{
    return _pressed;
}


