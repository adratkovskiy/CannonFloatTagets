#include "stdafx.h"
#include "Targets.h"

Targets::Targets(const float scale
	, const IRect& textureRect
	, const FPoint& pos
	, Render::Texture* texture
	, const FPoint& moveVec
	, const float speed
	, const int topBorder
	, const int bottomBorder
	, const int leftBorder
	, const int rightBorder
	, const int points
) :
	RoundObject(scale, textureRect, pos)
	, _texture(texture)
	, _moveVec(moveVec)
	, _speed(speed)
	, _topBorder(topBorder)
	, _bottomBorder(bottomBorder)
	, _leftBorder(leftBorder)
	, _rightBorder(rightBorder)
	, _points(points)
{
}

Targets::~Targets()
{
}


void Targets::Draw() const
{
	_texture->Draw();
}

void Targets::Tick()
{
	if (RoundObject::getCoordCenter().x < _leftBorder) {
		setPos(FPoint{ _leftBorder - getRadius() , getPos().y });
		Collision(FPoint{ 1,0 });
	}
	else if (RoundObject::getCoordCenter().x > _rightBorder) {
		setPos(FPoint{ _rightBorder - getRadius() , getPos().y });
		Collision(FPoint{ -1,0 });
	}
	else if (RoundObject::getCoordCenter().y > _topBorder) {
		setPos(FPoint{ getPos().x , _topBorder - getRadius() });
		Collision(FPoint{ 0,-1 });
	}
	else if (RoundObject::getCoordCenter().y < _bottomBorder) {
		setPos(FPoint{ getPos().x , _bottomBorder - getRadius() });
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

void Targets::tooClose(Targets& victim)
{
	float sumRadius = _radius + victim.getRadius();
	FPoint diff = RoundObject::getCoordCenter() - victim.getCoordCenter();
	float range = LocalFunctions::vecLen(diff);
	//��������� �����, ����� �� ���� �����������
	//����� ���� �� ���������, ��������� ����� ����������, ����� ���������� ����� ����
	//���� ����� ���� �������� ����� ��������, �� ���-�� ��� �������, ��� ��� ������ ��������
	//(�������� � ��� ��� ������)
	//�� ������, ��� ��� ����. ��� ��� �� ��������� ������ � �������
	while (sumRadius > range) 
	{
		setPos(_pos + -_moveVec);
		range = LocalFunctions::vecLen(RoundObject::getCoordCenter() - victim.getCoordCenter());
	}
	Collision(diff);
	victim.Collision(diff);
}

const int Targets::getPoints() const noexcept
{
	return _points;
}
