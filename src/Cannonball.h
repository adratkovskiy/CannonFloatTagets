#pragma once
class Cannonball
{
public:
	Cannonball(FPoint pos);

	FPoint& getPos();
	bool& getShow();
	void setShow(bool show);
	
private:
	float _scale;
	bool _show;
	FPoint _pos;
};

