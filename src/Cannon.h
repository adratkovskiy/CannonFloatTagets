#pragma once
class Cannon
{
public:
	Cannon(const float angle
		, const float scale
		, const FPoint& standPos
		, const FPoint& cannonRotatePoint
		, const FPoint& cannonCenter
	);

	float getAngle() const;
	float getScale() const;
	const FPoint& getCannonCenter() const;
	const FPoint& getCannonRotatePoint() const;
	const FPoint& getStandPos() const;

	void setAngle(const float angle);

private:
	float _angle;
	float _scale;
	const FPoint _standPos;
	const FPoint _cannonRotatePoint;
	const FPoint _cannonCenter;
};

