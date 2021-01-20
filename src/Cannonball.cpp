#include "stdafx.h"
#include "Cannonball.h"

Cannonball::Cannonball(const float scale
	, const IRect& textureRect
	, const FPoint& pos
	, const float speed
	, const int topBorder
	, const int bottomBorder
	, const int leftBorder
	, const int rightBorder
) : RoundObject(scale, textureRect, pos)
	, _speed(speed)
	, _flightTime(0)
	, _topBorder(topBorder)
	, _bottomBorder(bottomBorder)
	, _leftBorder(leftBorder)
	, _rightBorder(rightBorder)
{
	_centerOffset = FPoint({ textureRect.width / 2 * RoundObject::getScale(), textureRect.height / 2 * RoundObject::getScale() });
	_stop = true;
}


void Cannonball::Tick()
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
	else if (RoundObject::getCoordCenter().y < 0) {
		setStopped(true);
		/*setPos(FPoint{ getPos().x , _bottomBorder - getRadius() });
		Collision(FPoint{ 0,1 });*/
	}
	RoundObject::addVecToPos(_moveVec);
}

bool Cannonball::isStoped() const
{
	return _stop;
}

void Cannonball::Collision(const FPoint& normal)
{
	float coff = ((_moveVec.x * normal.x + _moveVec.y * normal.y) / (normal.x * normal.x + normal.y * normal.y));
	FPoint nextMove;
	nextMove.x = _moveVec.x - 2.0f * normal.x * coff;
	nextMove.y = _moveVec.y - 2.0f * normal.y * coff;
	_moveVec = nextMove;
}

void Cannonball::setMoveVec(const FPoint& moveVec)
{
	_moveVec = moveVec;
}

void Cannonball::setStopped(const bool stopped)
{
	_stop = stopped;
}

const FPoint& Cannonball::getMoveVec() const
{
	return _moveVec;
}

bool Cannonball::crossAsSphere(TargetsBlock& victim)
{
	return LocalFunctions::pointToPointRange(_posCenter, victim.getCoordCenter()) <= victim.getSize().x / 2 + _radius;
}

void Cannonball::tooClose(TargetsBlock& victim)
{
	FPoint vicPos = victim.getPos();
	FPoint vicTopRightPoint = vicPos + victim.getSize();
	//���������� ������ ���������� ���� ������������ ����
	if (_posCenter.x <= vicPos.x)
	{
		if (_posCenter.y <= vicPos.y) //������ �����
		{
			if (LocalFunctions::pointToPointRange(vicPos, _posCenter) <= _radius)
			{
				victim.hit();
				if (vicPos.x - _posCenter.x < vicPos.y - _posCenter.y) //��������� �� �����, ��� �� ������ ����� ����
				{
					shiftBack(FPoint{ _posCenter.x , vicPos.y }); //������ �����
					Collision(FPoint{ 0, -1 });
				}
				else
				{
					shiftBack(FPoint{ vicPos.x , _posCenter.y }); //�����
					Collision(FPoint{ -1, 0 });
				}
			}
				
		}
		else if ((_posCenter.y > vicPos.y) && (_posCenter.y <= vicTopRightPoint.y)) // ����� �����
		{
			if (vicPos.x - _posCenter.x <= _radius)
			{
				victim.hit();
				shiftBack(FPoint{ vicPos.x , _posCenter.y });
				Collision(FPoint{ -1, 0 });
			}
		}
		else if (_posCenter.y > vicTopRightPoint.y) //����� ������� ����
		{
			if (LocalFunctions::pointToPointRange(FPoint{vicPos.x, vicTopRightPoint.y }, _posCenter) <= _radius)
			{
				victim.hit();
				if (vicPos.x - _posCenter.x < vicPos.y - _posCenter.y) //��������� �� �����, ��� �� ������� ����� ����
				{
					shiftBack(FPoint{ _posCenter.x , vicTopRightPoint.y }); //������� �����
					Collision(FPoint{ 0, 1 });
				}
				else
				{
					shiftBack(FPoint{ vicPos.x , _posCenter.y }); //����� �����
					Collision(FPoint{ -1, 0 });
				}
			}
		}
	}
	else if ((_posCenter.x > vicPos.x) && (_posCenter.x < vicTopRightPoint.x))
	{
		if (_posCenter.y <= vicPos.y) //��� �����
		{
			if (vicPos.y - _posCenter.y <= _radius)
			{
				victim.hit();
				shiftBack(FPoint{ _posCenter.x , vicPos.y });
				Collision(FPoint{ 0, -1 });
			}
		}
		else if (_posCenter.y >= vicTopRightPoint.y) //��� �����
		{
			if (_posCenter.y - vicTopRightPoint.y <= _radius)
			{
				victim.hit();
				shiftBack(FPoint{ _posCenter.x , vicTopRightPoint.y });
				Collision(FPoint{ 0, 1 });
			}
		}
	}
	else
	{
		if (_posCenter.y <= vicPos.y) //������ ������
		{
			if (LocalFunctions::pointToPointRange(FPoint{ vicTopRightPoint.x, vicPos.y}, _posCenter) <= _radius)
			{
				victim.hit();
				if (vicPos.x - _posCenter.x < vicPos.y - _posCenter.y) //��������� �� �����, ��� �� ������ ����� ����
				{
					shiftBack(FPoint{ _posCenter.x , vicPos.y }); //������ �����
					Collision(FPoint{ 0, -1 });
				}
				else
				{
					shiftBack(FPoint{ vicTopRightPoint.x , _posCenter.y }); //������ �����
					Collision(FPoint{ 1, 0 });
				}
			}
		}
		else if ((_posCenter.y > vicPos.y) && (_posCenter.y <= vicTopRightPoint.y)) // ������ �����
		{
			if (_posCenter.x - vicPos.x <= _radius)
			{
				victim.hit();
				shiftBack(FPoint{ vicTopRightPoint.x , _posCenter.y });
				Collision(FPoint{ 1, 0 });
			}
				
		}
		else if (_posCenter.y > vicTopRightPoint.y) //������ ������� ����
		{
			if (LocalFunctions::pointToPointRange(vicTopRightPoint, _posCenter) <= _radius)
			{
				victim.hit();
				if (vicTopRightPoint.x - _posCenter.x < vicTopRightPoint.y - _posCenter.y) //��������� �� �����, ��� �� ������� ����� ����
				{
					Collision(FPoint{ 0, 1 });
				}
				else
				{
					shiftBack(FPoint{ vicTopRightPoint.x , _posCenter.y });
					Collision(FPoint{ 1, 0 });
				}
			}
		}
	}
}

void Cannonball::shiftBack(FPoint& pointOfCollision)
{
	//��������� �����, ����� �� ���� �����������
	//����� ���� �� ���������, ��������� ����� ����������, 
	//����� ���������� ����� ������� ���� ����� ������� �������, 
	//�� ��� �������, ��� ��� ���� �������� �� fps
	//(����� ����� ������� �������� � ��� ��� ������)
	//�� ������, ��� ��� ����. ��� ��� �� ��������� ������ � �������
	float range = LocalFunctions::vecLen(_posCenter - pointOfCollision);
	while (_radius > range)
	{
		setPos(_pos + -_moveVec * 0.2); //���������� �� ����-����
		range = LocalFunctions::vecLen(_posCenter - pointOfCollision);
	}
}

/*void Cannonball::setFlightTime(float cannonTimer)
{
	_flightTime = cannonTimer;
}*/



