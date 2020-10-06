#pragma once
class Cannonball
{
public:
	Cannonball(const FPoint& pos, float speed, const std::vector<float>& splinePoints);

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
	float _scale;
	bool _show;
	FPoint _centerPos;
	float _speed;
	float _flightTime;
	FPoint _currentPosition;
	TimedSpline<FPoint> _spline;
	std::vector<float> _splinePoints;
};

