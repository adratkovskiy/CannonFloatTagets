#pragma once
class Aim
{
public:
	Aim(const float scale, const IRect& bitmapRect);

	const float getScale() const noexcept;
	const FPoint& getCoordCenter() const noexcept;
private:
	const float _scale;
	FPoint _centerCoord;
};

