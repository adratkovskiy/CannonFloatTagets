#pragma once
class Cannonball
{
public:
	Cannonball(FPoint pos);

	const FPoint& getPos() const noexcept;
	const bool& getShow() const noexcept;

	void setShow(bool show);
	
private:
	float _scale;
	bool _show;
	FPoint _pos;
};

