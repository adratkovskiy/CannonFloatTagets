#include "stdafx.h"
#include "TargetsBlock.h"

TargetsBlock::TargetsBlock(const float scale, const IRect& textureRect, const int health):
	RectObject(scale, textureRect)
	, _health(health)
{
}

TargetsBlock::~TargetsBlock()
{
}

int TargetsBlock::getHealth() const
{
	return _health;
}

void TargetsBlock::setHealth(const int health)
{
	_health = health;
}
