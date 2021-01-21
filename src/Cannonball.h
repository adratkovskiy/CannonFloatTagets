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
		, const FPoint& moveVec
		, const int topBorder
		, const int bottomBorder
		, const int leftBorder
		, const int rightBorder
		, const float normalSpeed
	);

	bool Tick();
	bool isStoped() const;
	void collision(const FPoint& normal);
	void setMoveVec(FPoint& moveVec);
	void setStopped(const bool stopped);

	const FPoint& getMoveVec() const;
	bool crossAsSphere(TargetsBlock& victim);
	void tooClose(RectObject& victim, float moveVecShiftX);
	void shiftBack(FPoint& pointOfCollision);
	void changeMoveVec(const float x);
	
private:
	FPoint _centerOffset;
	bool _stop;
	const int _topBorder;
	const int _bottomBorder;
	const int _leftBorder;
	const int _rightBorder;
	FPoint _moveVec;
	float _moveVecShiftX;
	float _normalSpeed;
};

