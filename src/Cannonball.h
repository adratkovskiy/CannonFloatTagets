#pragma once
#include "RoundObject.h"

class Cannonball : 
	public RoundObject
{
public:
	Cannonball(const float scale
		, const IRect& textureRect
		, const FPoint& pos
		, float speed
		, const std::vector<float>& splinePoints
	);

	void updPosition(const float globalTimer);
	void splineClear() noexcept;

	const FPoint& getPosition() const noexcept;
	const bool& getShow() const noexcept;
	const float& getSpeed() const noexcept;
	const float& getFlightTime() const noexcept;
	TimedSpline<FPoint>& getSpline();

	void setShow(bool show);
	void setFlightTime(float cannonTimer);
	void setSpline(FPoint cannonCenter, FPoint mousePos);
	
private:
	bool _show;
	FPoint _centerPos;
	float _speed;
	float _flightTime;
	FPoint _currentPosition;
	TimedSpline<FPoint> _spline;
	std::vector<float> _splinePoints;
};

