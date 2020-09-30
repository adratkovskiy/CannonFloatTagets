#include "stdafx.h"
#include "GameController.h"

void GameController::setReadyToShot(bool readyToShot)
{
	_readyToShot = readyToShot;
}

void GameController::setGameState(GameStates gameState)
{
	_gameState = gameState;
}


