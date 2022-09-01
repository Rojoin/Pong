
#include "Game.h"
#include "HowTo.h"
#include "Menu.h"

GameStates gameState = GameStates::MainMenu;
extern Player players[2];
bool isProgramRunning = true;
void gameStatesController(GameStates& gameStates,bool& isGameRunning)
{
	

	switch (gameStates)
	{
	case GameStates::MainMenu:
		MenuState(gameStates);
		break;
	case GameStates::VsCpu:
	case GameStates::VsPlayer:
		GameLogic();
		break;
	case GameStates::Rules:
		RulesStates(gameStates);
		break;
	case GameStates::Exit:
		CloseWindow();
		break;
	default: ;
	}
}
void gameStatesDrawing(GameStates& gameStates)
{
	switch (gameStates)
	{
	case GameStates::MainMenu:
		MenuDraw();
		break;
	case GameStates::VsCpu:
	case GameStates::VsPlayer:
		{
		DrawGame();
		}
		break;
	case GameStates::Rules:
		RulesDraw();
		break;
	case GameStates::Exit:
		isProgramRunning = false;

		break;
	}
}

void game()
{
	InitWindow(screenWidth, screenHeight, "Pong");
	InitAudioDevice();
	SetTargetFPS(GetMonitorRefreshRate(0));
	isProgramRunning = true;
	
	bool isGameRunning;
	while (!WindowShouldClose()&& isProgramRunning)    // Detect window close button or ESC key
	{
		gameStatesController(gameState,isGameRunning);
		BeginDrawing();
		
		gameStatesDrawing(gameState);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
}
