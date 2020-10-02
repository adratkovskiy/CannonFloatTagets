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

	const float& getAngle() const noexcept;
	const float& getScale() const noexcept;
	const FPoint& getCannonCenter() const noexcept;
	const FPoint& getCannonRotatePoint() const noexcept;
	const FPoint& getStandPos() const noexcept;

	void setAngle(float angle);
private:
	float _angle;
	float _scale;
	FPoint _standPos;
	FPoint _cannonRotatePoint;
	FPoint _cannonCenter;
};

