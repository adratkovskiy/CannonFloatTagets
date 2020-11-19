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

/*Targets::Targets(const Targets& obj) :
	RoundObject(obj._scale, obj._textureRect, obj._pos)
	, _texture(obj._texture)
	, _moveVec(obj._moveVec)
	, _speed(obj._speed)
	, _topBorder(obj._topBorder)
	, _bottomBorder(obj._bottomBorder)
	, _leftBorder(obj._leftBorder)
	, _rightBorder(obj._rightBorder)
	, _points(obj._points)
{
}*/

Targets& Targets::operator=(const Targets& obj)
{
	if (&obj == this) {
		return *this;
	}
	RoundObject::_scale = obj.RoundObject::_scale;
	RoundObject::_radius = obj.RoundObject::_radius;
	RoundObject::_pos = obj.RoundObject::_pos;
	RoundObject::_posCenter = obj.RoundObject::_posCenter;
	RoundObject::_textureRect = obj.RoundObject::_textureRect;
	_texture = obj._texture;
	_moveVec = obj._moveVec;
	_speed = obj._speed;
	_topBorder = obj._topBorder;
	_bottomBorder = obj._bottomBorder;
	_leftBorder = obj._leftBorder;
	_rightBorder = obj._rightBorder;
	_points = obj._points;
	return *this;
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
	//отодвигаю назад, чтобы не было пересечения
	//можно было бы посчитать, насколько точно отодвинуть, чтобы расстояния между ними
	//было равно двум радиусам обоих объектов, но что-то мне кажется, что это сильно усложнит
	//(арксинус и еще три синуса)
	//не уверен, что это надо. Тут при их скоростях потери в пиксель
	while (sumRadius > range) 
	{
		setPos(_pos + -_moveVec);
		range = LocalFunctions::vecLen(RoundObject::getCoordCenter() - victim.getCoordCenter());
	}
	Collision(diff);
	victim.Collision(diff);
}

int Targets::getPoints() const
{
	return _points;
}
