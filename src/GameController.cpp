#include "stdafx.h"
#include "GameController.h"

GameController::GameController(GameStates gameState, bool readyToShot) : 
	_gameState(gameState)
	, _readyToShot(readyToShot)
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


