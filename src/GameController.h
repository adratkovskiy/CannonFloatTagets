#pragma once



class GameController
{
public:
	enum class GameStates {
		START_SCREEN,
		GAME,
		STOP
	};

	GameController(GameStates gameState, bool readyToShot, float weaponScale);
	
	bool& getReadyToShot();
	GameController::GameStates& getGameState();
	IPoint& getMousePos();
	float& getWeaponScale();

	void setReadyToShot(bool readyToShot);
	void setGameState(GameStates gameState);
	void setMousePos(IPoint mousePos);
	
private:
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
	float _weaponScale;

};

