#include "stdafx.h"
#include "GameController.h"

GameController::GameController(GameStates gameState, bool readyToShot, float timer) :
	_gameState(gameState)
	, _readyToShot(readyToShot)
	, _timer(timer)
{
}

const bool& GameController::getReadyToShot() const noexcept
{
	if (!_readyToShot) {
		bool popo = _readyToShot;
	}
	return _readyToShot;
}

const GameController::GameStates& GameController::getGameState() const noexcept
{
	return _gameState;
}

const IPoint& GameController::getMousePos()  const noexcept
{
	return _mousePos;
}

const float& GameController::getTimer() const noexcept
{
	return _timer;
}

void GameController::setReadyToShot(bool readyToShot)
{
	if (readyToShot != _readyToShot)
		_readyToShot = readyToShot;
}

void GameController::setGameState(GameStates gameState)
{
	_gameState = gameState;
}

void GameController::setMousePos(IPoint mousePos)
{
	_mousePos = mousePos;
}

void GameController::setTimer(float timer)
{
	_timer = timer;
}

float& GameController::changeTimer()
{
	return _timer;
}



