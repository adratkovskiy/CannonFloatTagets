#pragma once
#include "GameController.h"
#include "Cannonball.h"
#include "Cannon.h"
#include "Options.h"
#include "Aim.h"
#include "Button.h"
#include "RoundObject.h"
#include "Targets.h"
#include "Functions.h"

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

	void CreateTarget();
	void CreateTarget(FPoint& pos, FPoint& moveVec);
	void CreateSomeTarget(int count);
	void CreateColorTarget(const char color, const int count);

	void SetGameStatus(const GameController::GameStates state);

	const std::string getTitlePoins() const;
	void TestButtonsClick();

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
	Render::Texture* _targetYellowTexture;
	Render::Texture* _targetRedTexture;
	Render::Texture* _targetBlueTexture;
	Render::Texture* _buttonUpTexture;
	Render::Texture* _buttonDownTexture;

	//main screen
	Color _fadeBackground;
	IRect _blockScreen;
	FPoint _textEndgameTitlePos;
	FPoint _textEndgamePointsPos;
	std::string _textEndgameString;
	Color _panelBottomStatColor;
	Color _defTextColor;
	IRect _panelBottomStatSize;
	IRect _panelTopStatSize;
	std::string _textTitlePointsString;
	std::string _textTitleTimeoutString;
	int _targetsCountToGame;

	//targets
	float _targetRedScale;
	float _targetBlueScale;
	float _targetYellowScale;
	float _targetRedSpeed;
	float _targetBlueSpeed;
	float _targetYellowSpeed;
	int _targetRedPoints;
	int _targetBluePoints;
	int _targetYellowPoints;
	int _targetsCountRed;
	int _targetsCountBlue;
	int _targetsCountYellow;
	float _gameTimeMax;

	GameController* _gControl;
	Cannonball* _cannonball;
	Cannon* _cannon;
	Options* _options;
	Aim* _aim;
	Button* _button;
	Button* _button30Targets;
	Button* _buttonExperiment;
	Button* _buttonRestart;
	std::vector<Targets> _targets;
	int _topBorder;
	int _bottomBorder;
	int _leftBorder;
	int _rightBorder;
	int _gamePoints;
	uint8_t _fade;
	uint8_t _fadeMax;
	int _fadeSpeed;
	float _gameTimer;
	float _gameTimerMax;

	EffectsContainer _effCont;
	ParticleEffectPtr _effParticleSmoke;

	bool _showTestButtons;
};
