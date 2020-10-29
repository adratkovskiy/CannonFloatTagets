#pragma once

class Button
{
public:
	Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect);
	~Button();

	const bool click(const IPoint& mouse_pos);
	void noPressed() noexcept;

	const float getScale() const noexcept;
	const FPoint& getPos() const noexcept;
	const std::string& getText() const noexcept;
	const FPoint& getTextPos() const noexcept;
	const bool getPressed() const noexcept;

	void setActive(const bool active) noexcept;

private:
	bool _active;
	bool _pressed;
	const FPoint _pos;
	FPoint _textPos;
	FPoint _size;
	const float _scale;
	const std::string _text;

};

