#pragma once
#include "Functions.h"

class RoundObject
{
public:
	RoundObject(const float scale, const IRect& textureRect, const FPoint& pos);
	const bool isCrossing(const FPoint& targetCoord, const float targetRadius);

	const FPoint& getPos() const noexcept;
	const float getScale() const noexcept;
	const float getRadius() const noexcept;
	const FPoint& getCoordCenter() noexcept;

	void setPos(FPoint& pos);
	void addVecToPos(FPoint& vec);

protected:
	const float _scale;
	float _radius;
	FPoint _pos;
	FPoint _posCenter;

private:
	void setPosCenter();
};

