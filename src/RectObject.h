#pragma once
class RectObject
{
public:
	RectObject(const float scale
		, const IRect& textureRect
		, const FPoint& pos
	);
	virtual ~RectObject();
	float getScale() const;
	const FPoint& getPos() const;
	const FPoint& getCoordCenter() const;
	const FPoint& getSize() const;

	void setPos(const FPoint& pos);
	void setPosCenter(const FPoint& pos);
	void setPosCenter(const float posCenter);

protected:
	float _scale;
	FPoint _size;
	FPoint _centerOffset;
	IRect _textureRect;
	FPoint _pos;
	FPoint _posCenter;

private:
	void setPosCenter();
};

