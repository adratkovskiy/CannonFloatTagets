#pragma once
class GameController
{
public:
	enum gameStates {
		START_SCREEN,
		GAME,
		STOP
	};
	GameController(gameStates gameState);

	bool getReadyToShot() const { return _readyToShot; };
	bool getGameState() const { return _gameState; };
	void setReadyToShot(bool readyToShot);
	
private:
	bool _readyToShot = false;
	gameStates _gameState;
};

