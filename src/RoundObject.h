#pragma once
class RoundObject
{
public:
	enum class targetType {
		YELLOW,
		RED,
		BLUE
	};
	RoundObject(const float scale, const IRect& textureRect, FPoint& centerPos, targetType type);

	const RoundObject::targetType& getType() const noexcept;
	const FPoint& getPos() const noexcept;
	const float getScale() const noexcept;

private:
	const float _scale;
	float _radius;
	FPoint _centerPos;
	targetType _type;
};

