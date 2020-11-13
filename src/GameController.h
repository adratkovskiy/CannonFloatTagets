#pragma once



class GameController
{
public:
	enum class GameStates {
		START_SCREEN,
		GAME,
		TO_STOP,
		STOP
	};

	GameController(GameStates gameState, bool readyToShot, float timer);

	float& changeTimer();

	bool getReadyToShot() const;
	const GameController::GameStates& getGameState() const;
	const IPoint& getMousePos() const;
	float getTimer() const;

	void setReadyToShot(const bool readyToShot);
	void setGameState(const GameStates gameState);
	void setMousePos(const IPoint& mousePos);
	void setTimer(const float timer);
	
private:
	float _timer;
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
};

