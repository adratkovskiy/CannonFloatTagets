#pragma once
#include "Functions.h"

class RoundObject
{
public:
	RoundObject(const float scale, const IRect& textureRect, const FPoint& pos);
	bool isCrossing(const FPoint& targetCoord, const float targetRadius);
	void addVecToPos(FPoint& vec);

	const FPoint& getPos() const;
	float getScale() const;
	float getRadius() const;
	const FPoint& getCoordCenter();

	void setPos(FPoint& pos);

protected:
	float _scale;
	float _radius;
	FPoint _pos;
	FPoint _posCenter;

private:
	void setPosCenter();
};

