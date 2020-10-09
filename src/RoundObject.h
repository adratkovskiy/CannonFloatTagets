#pragma once
class RoundObject
{
public:
	RoundObject(const float scale, const IRect& textureRect, FPoint& pos);

	const FPoint& getPos() const noexcept;
	const float getScale() const noexcept;
	const float getRadius() const noexcept;
	const FPoint& getCoordCenter() noexcept;

private:
	const float _scale;
	float _radius;
	FPoint _pos;
};

