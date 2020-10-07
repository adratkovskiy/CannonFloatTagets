#pragma once
class Button
{
public:
	Button(const FPoint& pos, const float scale, const std::string& text);
	~Button();

	const float getScale() const noexcept;
	const FPoint& getPos() const noexcept;
	const std::string& getText() const noexcept;

private:
	FPoint _pos;
	float _scale;
	std::string _text;

};

