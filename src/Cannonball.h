#pragma once
#include "RoundObject.h"
#include "TargetsBlock.h"
#include "Functions.h"

class Cannonball : 
	public RoundObject
{
public:
	Cannonball(const float scale
		, const IRect& textureRect
		, const FPoint& pos
		, const float speed
		, const int topBorder
		, const int bottomBorder
		, const int leftBorder
		, const int rightBorder
		, const float moveVectorShiftX
	);

	void Tick();
	bool isStoped() const;
	void collision(const FPoint& normal);
	void setMoveVec(const FPoint& moveVec);
	void setStopped(const bool stopped);

	const FPoint& getMoveVec() const;
	bool crossAsSphere(TargetsBlock& victim);
	void tooClose(RectObject& victim, float moveVecShiftX);
	void shiftBack(FPoint& pointOfCollision);
	void changeMoveVec(const float x);
	
private:
	FPoint _centerOffset;
	const float _speed;
	float _flightTime;
	TimedSpline<FPoint> _spline;
	std::vector<float> _splinePoints;
	bool _stop;
	int _topBorder;
	int _bottomBorder;
	int _leftBorder;
	int _rightBorder;
	FPoint _moveVec;
	float _moveVecShiftX;
};

