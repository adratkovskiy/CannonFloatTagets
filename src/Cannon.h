#pragma once
class Cannon
{
public:
	Cannon(float angle);
	float* getAngle() { return &_angle; };
	void setAngle(float angle) { _angle = angle; };
private:
	float _angle;
};

