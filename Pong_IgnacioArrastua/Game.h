#pragma once
#include "GameLoop.h"
#include "GameStates.h"


void gameStatesDrawing(GameStates& gameStates);
	void gameStatesController(GameStates& gameStates, Player players[], bool& isGameRunning);
	void game();