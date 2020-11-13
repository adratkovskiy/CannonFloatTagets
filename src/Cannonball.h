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

<<<<<<< HEAD
	const FPoint& getPosition() const;
	float getSpeed() const;
	float getFlightTime() const;
	TimedSpline<FPoint>& getSpline();
=======
	const FPoint& getPosition() const noexcept;
	const bool& getShow() const noexcept;
	const float& getSpeed() const noexcept;
	const float& getFlightTime() const noexcept;
	TimedSpline<FPoint>& getSpline() noexcept;
>>>>>>> 22a3e1faecb604078384831bf2c8f0ebd8be7e8a

	void setShow(bool show);
	void setFlightTime(float cannonTimer);
	void setSpline(FPoint cannonCenter, FPoint mousePos);
	
private:
	bool _show;
	FPoint _centerPos;
	const float _speed;
	float _flightTime;
	FPoint _currentPosition;
	TimedSpline<FPoint> _spline;
	std::vector<float> _splinePoints;
};

