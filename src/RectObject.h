#pragma once
class RectObject
{
public:
	RectObject(const float scale
		, const IRect& textureRect
	);
	virtual ~RectObject();
	float getScale() const;
	const FPoint& getPos() const;
	const FPoint& getCoordCenter() const;

	void setPos(const FPoint& pos);
	void setPosCenter(const FPoint& pos);
	void setPosCenter(const float posCenter);

protected:
	float _scale;
	FPoint _centerOffset;
	IRect _textureRect;
	FPoint _pos;
	FPoint _posCenter;

private:
	void setPosCenter();
};

