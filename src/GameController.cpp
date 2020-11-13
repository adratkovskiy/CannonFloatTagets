#include "stdafx.h"
#include "GameController.h"

GameController::GameController(GameStates gameState, bool readyToShot, float timer) :
	_gameState(gameState)
	, _readyToShot(readyToShot)
	, _timer(timer)
{
}

bool GameController::getReadyToShot() const
{
	return _readyToShot;
}

const GameController::GameStates& GameController::getGameState() const
{
	return _gameState;
}

const IPoint& GameController::getMousePos()  const
{
	return _mousePos;
}

float GameController::getTimer() const
{
	return _timer;
}

void GameController::setReadyToShot(const bool readyToShot)
{
	_readyToShot = readyToShot;
}

void GameController::setGameState(const GameStates gameState)
{
	_gameState = gameState;
}

void GameController::setMousePos(const IPoint& mousePos)
{
	_mousePos = mousePos;
}

void GameController::setTimer(const float timer)
{
	_timer = timer;
}

float& GameController::changeTimer()
{
	return _timer;
}



