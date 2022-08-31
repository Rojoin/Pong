#pragma once
#include "GameLoop.h"
#include "GameStates.h"


void GameStatesDrawing(GameStates& gameStates);
	void GameStatesController(GameStates& gameStates, Player players[], bool& isGameRunning);
	void Game();