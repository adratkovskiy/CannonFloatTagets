#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale
	, const IRect& textureRect
	, FPoint& pos
	, Render::Texture* texture
	, FPoint& moveVec
	, const float speed) :
	RoundObject(scale, textureRect, pos)
	, _texture(texture)
	, _moveVec(moveVec)
	, _speed(speed)
{
}


void Targets::Draw() const
{
	_texture->Draw();
}

void Targets::Tick()
{
	RoundObject::addVecToPos(_moveVec);
	if (RoundObject::getPos().x < 100) {
		FPoint stenka = { 0, 1 };
		FPoint normal = { -1, 0 };
		float coff = ((_moveVec.x * normal.x + _moveVec.y * normal.y) / (normal.x * normal.x + normal.y * normal.y));
		FPoint nextMove;
		nextMove.x = _moveVec.x - 2.0f * normal.x * coff;
		nextMove.y = _moveVec.y - 2.0f * normal.y * coff;
		_moveVec = nextMove;
	}
}
