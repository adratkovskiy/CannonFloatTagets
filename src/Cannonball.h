#pragma once
#include "RoundObject.h"

class Cannonball : 
	public RoundObject
{
public:
	Cannonball(const float scale
		, const IRect& textureRect
		, const FPoint& pos
		, const float speed
		, const std::vector<float>& splinePoints
	);

	void updPosition(const float globalTimer);
	void splineClear();

	float getSpeed() const;
	//float getFlightTime() const;
	//TimedSpline<FPoint>& getSpline();
	bool isStoped() const;

	void setFlightTime(float cannonTimer);
	void setSpline(FPoint cannonCenter, FPoint mousePos);
	
private:
	FPoint _centerOffset;
	const float _speed;
	float _flightTime;
	TimedSpline<FPoint> _spline;
	std::vector<float> _splinePoints;
	bool _stop;
};

