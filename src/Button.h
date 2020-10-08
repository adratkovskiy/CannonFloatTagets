#pragma once
class Button
{
public:
	Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect);
	~Button();

	void click(const IPoint& mouse_pos);
	void noPressed() noexcept;

	const float getScale() const noexcept;
	const FPoint& getPos() const noexcept;
	const std::string& getText() const noexcept;
	const FPoint& getTextPos() const noexcept;
	const bool getPressed() const noexcept;

private:
	bool _pressed;
	FPoint _pos;
	FPoint _textPos;
	FPoint _size;
	float _scale;
	std::string _text;

};

