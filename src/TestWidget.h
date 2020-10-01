#pragma once
#include "GameController.h"
#include "Cannonball.h"

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

	std::string logStr;

private:
	void Init();

private:
	float _timer;
	float _cannonTimer = 2;
	float _angle;
	float _shotLenth;
	IPoint _standPos = { 480, 10 };
	IPoint _cannonRotatePoint = { -40, -32 };
	IPoint _cannonCenter = { 535, 62 };
	IPoint _mousePos;
	IPoint _cannonballPos;
	IPoint _cannonballCenter = { -20, -20 };
	
	
	Render::Texture* _cannonBack;
	Render::Texture* _cannonFront;
	Render::Texture* _stand;
	Render::Texture* _background;
	Render::Texture* _aim;
	Render::Texture* _point;
	Render::Texture* _cannonbalPic;
	int _curTex;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

	TimedSpline<FPoint> spline;
	GameController* _gControl;
	Cannonball* _cannonball;
};
