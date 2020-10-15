#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale
	, const IRect& textureRect
	, FPoint& pos
	, Render::Texture* texture
	, FPoint& moveVec
	, const float speed
	, const int topBorder
	, const int bottomBorder
	, const int leftBorder
	, const int rightBorder
) :
	RoundObject(scale, textureRect, pos)
	, _texture(texture)
	, _moveVec(moveVec)
	, _speed(speed)
	, _topBorder(topBorder)
	, _bottomBorder(bottomBorder)
	, _leftBorder(leftBorder)
	, _rightBorder(rightBorder)
{
}


void Targets::Draw() const
{
	_texture->Draw();
}

void Targets::Tick()
{
	if (RoundObject::getCoordCenter().x < _leftBorder) {
		Collision(FPoint{ 1,0 });
	}
	else if (RoundObject::getCoordCenter().x > _rightBorder) {
		Collision(FPoint{ -1,0 });
	}
	else if (RoundObject::getCoordCenter().y > _topBorder) {
		Collision(FPoint{ 0,-1 });
	}
	else if (RoundObject::getCoordCenter().y < _bottomBorder) {
		Collision(FPoint{ 0,1 });
	}
	RoundObject::addVecToPos(_moveVec);
}

void Targets::Collision(const FPoint& normal)
{
	float coff = ((_moveVec.x * normal.x + _moveVec.y * normal.y) / (normal.x * normal.x + normal.y * normal.y));
	FPoint nextMove;
	nextMove.x = _moveVec.x - 2.0f * normal.x * coff;
	nextMove.y = _moveVec.y - 2.0f * normal.y * coff;
	_moveVec = nextMove;
}

void Targets::tooClose(const FPoint& victimCoord, const float victimRaduis)
{
	FPoint diff = RoundObject::getCoordCenter() - victimCoord;
	float range = LocalFunctions::vecLen(diff);
	float summRadius = victimRaduis + _radius;
	float needRadius = summRadius - range + 1.f;
	Collision({ diff.y, diff.x });
}
