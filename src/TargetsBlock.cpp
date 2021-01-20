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
	RectObject(scale, textureRect, pos, health)
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

void TargetsBlock::click(const IPoint& mouse_pos)
{
	FPoint pos = getPos();
	if ((mouse_pos.x >= pos.x)
		&& (mouse_pos.x <= pos.x + _size.x)
		&& (mouse_pos.y >= pos.y)
		&& (mouse_pos.y <= pos.y + _size.y)
		) {
		*_toLeft = !*_toLeft;
	}
}

void TargetsBlock::move()
{
	FPoint pos = getPos();
	*_toLeft ? pos.x -= _speed : pos.x += _speed;
	if (pos.x <= _leftBorder)
	{
		*_toLeft = !*_toLeft;
		pos.x += _speed * 2; //компенсация порядка разворота движения
	}
		
	if (pos.x + _size.x >= _rightBorder)
		*_toLeft = !*_toLeft;
	setPos(pos);

}


