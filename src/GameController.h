#pragma once



class GameController
{
public:
	enum class GameStates {
		START_SCREEN,
		GAME,
		STOP
	};

	GameController(GameStates gameState, bool readyToShot);
	
	bool& getReadyToShot();
	GameController::GameStates& getGameState();
	IPoint& getMousePos();

	void setReadyToShot(bool readyToShot);
	void setGameState(GameStates gameState);
	void setMousePos(IPoint mousePos);
	
private:
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
};

