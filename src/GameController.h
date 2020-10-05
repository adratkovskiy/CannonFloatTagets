#pragma once



class GameController
{
public:
	enum class GameStates {
		START_SCREEN,
		GAME,
		STOP
	};

	GameController(GameStates gameState, bool readyToShot, float timer);
	
	const bool getReadyToShot() const noexcept;
	const GameController::GameStates& getGameState() const noexcept;
	const IPoint& getMousePos() const noexcept;
	const float getTimer() const noexcept;

	void setReadyToShot(const bool readyToShot);
	void setGameState(const GameStates gameState);
	void setMousePos(const IPoint& mousePos);
	void setTimer(const float timer);
	float& changeTimer();
	
private:
	float _timer;
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
};

