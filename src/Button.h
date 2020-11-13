#pragma once

class Button
{
public:
	Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect);
	~Button();

	bool click(const IPoint& mouse_pos);
	void noPressed();

	float getScale() const;
	const FPoint& getPos() const;
	const std::string& getText() const;
	const FPoint& getTextPos() const;
	bool getPressed() const;

	void setActive(const bool active);

private:
	bool _active;
	bool _pressed;
	const FPoint _pos;
	FPoint _textPos;
	FPoint _size;
	const float _scale;
	const std::string _text;

};

