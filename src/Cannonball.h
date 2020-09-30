#pragma once
class Cannonball
{
public:
	Cannonball(IPoint pos);
	IPoint getPos() const { return _pos; }
	void setShow(bool show) { _show = show;  }
	bool getShow() const { return _show; }
private:
	float _scale;
	bool _show = false;
	IPoint _pos;
};

