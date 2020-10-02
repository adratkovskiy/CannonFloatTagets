#include "stdafx.h"
#include "GameController.h"

GameController::GameController(GameStates gameState, bool readyToShot) : 
	_gameState(gameState)
	, _readyToShot(readyToShot)
{
}

bool& GameController::getReadyToShot()
{
	if (!_readyToShot) {
		bool popo = _readyToShot;
	}
	return _readyToShot;
}

GameController::GameStates& GameController::getGameState()
{
	return _gameState;
}

IPoint& GameController::getMousePos()
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


