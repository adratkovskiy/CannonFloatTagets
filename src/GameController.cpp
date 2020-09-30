#include "stdafx.h"
#include "GameController.h"

GameController::GameController(gameStates gameState) : _gameState(gameState)
{
}

void GameController::setReadyToShot(bool readyToShot)
{
	_readyToShot = readyToShot;
}
