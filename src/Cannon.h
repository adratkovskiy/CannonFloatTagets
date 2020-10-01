#pragma once
class Cannon
{
public:
	Cannon(float angle);

	float& getAngle();

	void setAngle(float angle);
private:
	float _angle;
};

