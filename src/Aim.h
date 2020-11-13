#pragma once
class Aim
{
public:
	Aim(const float scale, const IRect& bitmapRect);

	float getScale() const;
	const FPoint& getCoordCenter() const;
private:
	float _scale;
	FPoint _centerCoord;
};

