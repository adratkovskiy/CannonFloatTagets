#pragma once
#include "GameController.h"
#include "Cannonball.h"
#include "Cannon.h"
#include "Options.h"
#include "Aim.h"
#include "Button.h"

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
	
	Render::Texture* _cannonBackTexture;
	Render::Texture* _cannonFrontTexture;
	Render::Texture* _standTexture;
	Render::Texture* _backgroundTexture;
	Render::Texture* _aimTexture;
	Render::Texture* _pointTexture;
	Render::Texture* _cannonballTexture;
	Render::Texture* _targetTexture;
	Render::Texture* _buttonUpTexture;
	Render::Texture* _buttonDownTexture;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	GameController* _gControl;
	Cannonball* _cannonball;
	Cannon* _cannon;
	Options* _options;
	Aim* _aim;
	Button* _button;
};
