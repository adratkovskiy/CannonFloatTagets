#pragma once
#include "GameController.h"
#include "Cannonball.h"
//#include "Cannon.h"
#include "Options.h"
#include "Aim.h"
#include "Button.h"
#include "RoundObject.h"
#include "Targets.h"
#include "Functions.h"
#include "Player.h"
#include "TargetsBlock.h"

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

	void CreateTarget(FPoint& pos
		, int health
		, float speed
		, bool* toLeft
	);
	void CreateLevel();

	void SetGameStatus(const GameController::GameStates state);

	const std::string getTitlePoins() const;

private:
	void Init();

private:
	
	Render::Texture* _backgroundTexture;
	//Render::Texture* _pointTexture;
	Render::Texture* _cannonballTexture;
	Render::Texture* _buttonUpTexture;
	Render::Texture* _buttonDownTexture;
	Render::Texture* _invaderTexture_0;
	Render::Texture* _invaderTexture_1;
	Render::Texture* _invaderTexture_2;
	Render::Texture* _invaderTexture_3;
	Render::Texture* _invaderTexture_4;

	Render::Texture* _playerTexture;

	//main screen
	Color _fadeBackground;
	FPoint _gameScreen;
	IRect _blockScreen;
	FPoint _textEndgameTitlePos;
	FPoint _textEndgameResultPos;
	std::string _textEndgameString;
	std::string _textTitleResultString;
	std::string _textTitleSecString;

	Color _panelBottomStatColor;
	Color _defTextColor;
	IRect _panelBottomStatSize;
	IRect _panelTopStatSize;
	std::string _textTitleTimerString;
	int _targetsCountToGame;

	//targets
	float _gameTimeMax;
	float _playerScale;
	FPoint _playerSpawn;

	Player* _player;
	GameController* _gControl;
	Cannonball* _cannonball;
	Options* _options;
	Options* _levels;
	Button* _buttonRestart;
	std::vector<TargetsBlock*> _targetsBlock;
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
	float _targetVPadding;
	float _topPadding;
	float _targetHPadding;
	float _targetScale;
	FRect _targetSize;
	std::vector<bool*>_targetMoveToLeft;
	FPoint _cannonballPointOnPlayer;

	EffectsContainer _effCont;
	ParticleEffectPtr _effParticleSmoke;

	bool _showTestButtons;
	float _shiftMultiplier;
	std::vector<bool*> _levelDirection;
};
