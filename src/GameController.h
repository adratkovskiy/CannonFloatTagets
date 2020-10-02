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
	
	const bool& getReadyToShot() const noexcept;
	const GameController::GameStates& getGameState() const noexcept;
	const IPoint& getMousePos() const noexcept;

	void setReadyToShot(bool readyToShot);
	void setGameState(GameStates gameState);
	void setMousePos(IPoint mousePos);
	
private:
	IPoint _mousePos;
	bool _readyToShot;
	GameStates _gameState;
};

