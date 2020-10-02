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
	
	const bool& getReadyToShot() const noexcept;
	const GameController::GameStates& getGameState() const noexcept;
	const IPoint& getMousePos() const noexcept;
	const float& getTimer() const noexcept;

	void setReadyToShot(bool readyToShot);
	void setGameState(GameStates gameState);
	void setMousePos(IPoint mousePos);
	void setTimer(float timer);
	float& changeTimer();
	
private:
	float _timer;
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
};

