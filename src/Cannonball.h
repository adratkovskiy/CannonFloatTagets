#pragma once
class Cannonball
{
public:
	Cannonball(FPoint pos, float speed);

	const FPoint& getPos() const noexcept;
	const bool& getShow() const noexcept;
	const float& getSpeed() const noexcept;
	const float& getCannonTimer() const noexcept;

	void setShow(bool show);
	void setCannonTimer(float cannonTimer);
	
private:
	float _scale;
	bool _show;
	FPoint _pos;
	float _speed;
	float _cannonTimer;
};

