#pragma once
#include "GameController.h"

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
/// 


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
	float _gunScale = 0.125f;
	IPoint _standPos = { 480, 10 };
	IPoint _cannonRotatePoint = { -40, -32 };
	IPoint _cannonCenter = { 535, 62 };
	IPoint _mouse_pos;
	
	Render::Texture* _cannon;
	Render::Texture* _stand;
	Render::Texture* _background;
	Render::Texture* _aim;
	Render::Texture* _point;
	int _curTex;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

	TimedSpline<FPoint> spline;
	GameController* _gControl;
};
