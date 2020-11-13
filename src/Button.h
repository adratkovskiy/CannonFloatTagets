#pragma once

class Button
{
public:
	Button(const FPoint& pos, const float scale, const std::string& text, IRect& textureRect);
	~Button();

	bool click(const IPoint& mouse_pos);
	void noPressed();

<<<<<<< HEAD
	float getScale() const;
	const FPoint& getPos() const;
	const std::string& getText() const;
	const FPoint& getTextPos() const;
	bool getPressed() const;
	void setActive(const bool active);
=======
	const float getScale() const noexcept;
	const FPoint& getPos() const noexcept;
	const std::string& getText() const noexcept;
	const FPoint& getTextPos() const noexcept;
	const bool getPressed() const noexcept;

	void setActive(const bool active) noexcept;
>>>>>>> 22a3e1faecb604078384831bf2c8f0ebd8be7e8a

private:
	bool _active;
	bool _pressed;
	const FPoint _pos;
	FPoint _textPos;
	FPoint _size;
	const float _scale;
	const std::string _text;

};

