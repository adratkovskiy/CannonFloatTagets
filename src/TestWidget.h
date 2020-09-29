#pragma once

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
/// 

struct pointsXY {
	float X;
	float Y;
};

class TestWidget : public GUI::Widget
{
public:
	TestWidget(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;

	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;

private:
	void Init();

private:
	float _timer;
	
	float _scale;
	float _angle;
	float _standScale = 0.125f;
	int _standPosX = 480;
	int _standPosY = 10;
	float _cannonScale = 0.125f;
	int _cannonPosX = 495;
	int _cannonPosY = 30;
	int _cannonRotatePointX = -40;
	int _cannonRotatePointY = -32;
	int _pointX = 0;
	int _pointY = 0;
	pointsXY Machine;
	pointsXY Destination;
	
	Render::Texture* _cannon;
	Render::Texture* _stand;
	Render::Texture* _background;
	Render::Texture* _aim;
	int _curTex;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

	TimedSpline<FPoint> spline;
};
