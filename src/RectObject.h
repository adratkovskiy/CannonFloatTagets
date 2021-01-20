#pragma once
class RectObject
{
public:
	RectObject(const float scale
		, const IRect& textureRect
		, const FPoint& pos
		, const int health
	);
	virtual ~RectObject();
	float getScale() const;
	const FPoint& getPos() const;
	const FPoint& getCoordCenter() const;
	const FPoint& getSize() const;

	void setPos(const FPoint& pos);
	void setPosCenter(const FPoint& pos);
	void setPosCenter(const float posCenterX);

	void hit();

protected:
	float _scale;
	FPoint _size;
	FPoint _centerOffset;
	IRect _textureRect;
	int _health;

private:
	void setPosCenter();
	FPoint _pos;
	FPoint _posCenter;
};

