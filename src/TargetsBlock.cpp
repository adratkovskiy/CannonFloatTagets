#include "stdafx.h"
#include "TargetsBlock.h"

TargetsBlock::TargetsBlock(const float scale
	, const IRect& textureRect
	, const FPoint& pos
	, const int health
	, const float speed
	, bool* toLeft
	, const int leftBorder
	, const int rightBorder
):
	RectObject(scale, textureRect, pos)
	, _health(health)
	, _speed(speed)
	, _toLeft(toLeft)
	, _leftBorder(leftBorder)
	, _rightBorder(rightBorder)
{
}

TargetsBlock::~TargetsBlock()
{
}

int TargetsBlock::getHealth() const
{
	return _health;
}

bool* TargetsBlock::getToLeft()
{
	return _toLeft;
}

void TargetsBlock::setHealth(const int health)
{
	_health = health;
}

void TargetsBlock::click(const IPoint& mouse_pos)
{
	if ((mouse_pos.x >= _pos.x)
		&& (mouse_pos.x <= _pos.x + _size.x)
		&& (mouse_pos.y >= _pos.y)
		&& (mouse_pos.y <= _pos.y + _size.y)
		) {
		*_toLeft = !*_toLeft;
	}
}

void TargetsBlock::move()
{
	*_toLeft ? _pos.x -= _speed : _pos.x += _speed;
	if (_pos.x <= _leftBorder)
	{
		*_toLeft = !*_toLeft;
		_pos.x += _speed * 2; //компенсация порядка разворота движения
	}
		
	if (_pos.x + _size.x >= _rightBorder)
		*_toLeft = !*_toLeft;
}

void TargetsBlock::hit()
{
	_health--;
}

