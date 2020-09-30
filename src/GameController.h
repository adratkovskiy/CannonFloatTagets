#pragma once
class GameController
{
public:
	enum class GameStates {
		START_SCREEN,
		GAME,
		STOP
	};
	GameController(GameStates gameState) : _gameState(gameState) {};

	bool getReadyToShot() const { return _readyToShot; };
	GameStates getGameState() const { return _gameState; };
	void setReadyToShot(bool readyToShot);
	void setGameState(GameStates gameState);
	
private:
	bool _readyToShot = false;
	GameStates _gameState;
};

