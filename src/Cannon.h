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

	const float getAngle() const noexcept;
	const float getScale() const noexcept;
	const FPoint& getCannonCenter() const noexcept;
	const FPoint& getCannonRotatePoint() const noexcept;
	const FPoint& getStandPos() const noexcept;

	void setAngle(const float angle);
private:
	float _angle;
	const float _scale;
	const FPoint _standPos;
	const FPoint _cannonRotatePoint;
	const FPoint _cannonCenter;
};

