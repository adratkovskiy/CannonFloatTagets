#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale
	, const IRect& textureRect
	, FPoint& pos
	, Render::Texture* texture
	, float moveAngle
	, float speed) :
	RoundObject(scale, textureRect, pos)
	, _texture(texture)
	, _moveAngle(moveAngle)
	, _speed(speed)
{
	_moveVec.x = _speed * math::sin(_moveAngle);
	_moveVec.y = _speed * math::cos(_moveAngle);
}


void Targets::Draw() const
{
	_texture->Draw();
}

void Targets::Tick()
{
	RoundObject::addVecToPos(_moveVec);
}
