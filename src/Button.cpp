#include "stdafx.h"
#include "Button.h"

Button::Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect) :
    _pos(pos)
    , _scale(scale)
    , _text(text)
    , _pressed(false)
    , _active(true)
{
    _size.x = textureRect.width * _scale;
    _size.y = textureRect.height * _scale;
    _textPos = pos + _size / 2;
}

Button::~Button()
{
}

bool Button::click(const IPoint& mouse_pos)
{
    if (_active) { 
        if ((mouse_pos.x >= _pos.x)
            & (mouse_pos.x <= _pos.x + _size.x)
            & (mouse_pos.y >= _pos.y)
            & (mouse_pos.y <= _pos.y + _size.y)
            ) {
            _pressed = true;
        }
    }
    return _pressed;
}

void Button::noPressed()
{
    _pressed = false;
}

float Button::getScale() const
{
    return _scale;
}

const FPoint& Button::getPos() const
{
    return _pos;
}

const std::string& Button::getText() const
{
    return _text;
}

const FPoint& Button::getTextPos() const
{
    return _textPos;
}

bool Button::getPressed() const
{
    return _pressed;
}

void Button::setActive(const bool active)
{
    _active = active;
}


