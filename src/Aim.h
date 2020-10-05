#pragma once
class Aim
{
public:
	Aim(const float scale, const IRect& bitmapRect);

	const float getScale() const noexcept;
private:
	const float _scale;
	const IRect _bitmapRect;
};

