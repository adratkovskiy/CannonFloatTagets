#pragma once
class Cannon
{
public:
	Cannon(float angle
		, float scale
		, FPoint standPos
		, FPoint cannonRotatePoint
		, FPoint cannonCenter
	);

	float& getAngle();
	float& getScale();
	FPoint& getCannonCenter();
	FPoint& getCannonRotatePoint();
	FPoint& getStandPos();

	void setAngle(float angle);
private:
	float _angle;
	float _scale;
	FPoint _standPos;
	FPoint _cannonRotatePoint;
	FPoint _cannonCenter;
};

