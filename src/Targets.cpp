#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale, const IRect& textureRect, FPoint& pos, Render::Texture* texture, float moveAngle) :
	RoundObject(scale, textureRect, pos)
	, _texture(texture)
	, _moveAngle(moveAngle)
{
}


void Targets::Draw() const
{
	_texture->Draw();
}

void Targets::Tick()
{
	FPoint pos = RoundObject::getPos();
	pos.x = pos.x + _speed * math::sin(_moveAngle);
	pos.y = pos.y + _speed * math::cos(_moveAngle);
	RoundObject::setPos(pos);
}
