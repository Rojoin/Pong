
#include "Game.h"

#include "Menu.h"

GameStates gameState = GameStates::MainMenu;
extern Player players[2];
void GameStatesController(GameStates& gameStates,bool& isGameRunning)
{
	

	switch (gameStates)
	{
	case GameStates::MainMenu:
		MenuState(gameStates);
		break;
	case GameStates::VsCpu: break;
	case GameStates::VsPlayer:
		GameLogic();
		break;
	case GameStates::Rules: break;
	case GameStates::Options: break;
	case GameStates::Exit: break;
	default: ;
	}
}
void GameStatesDrawing(GameStates& gameStates)
{
	switch (gameStates)
	{
	case GameStates::MainMenu:
		MenuDraw();
		break;
	case GameStates::VsCpu:
		break;
	case GameStates::VsPlayer:
		{
		DrawGame();
		}
		break;

	case GameStates::Rules:
		break;
	case GameStates::Options:
		break;
	case GameStates::Exit:
		break;
	}
}

void Game()
{
	InitWindow(screenWidth, screenHeight, "Pong");
	InitAudioDevice();
	SetTargetFPS(GetMonitorRefreshRate(0));
	
	
	bool isGameRunning;
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		GameStatesController(gameState,isGameRunning);
		BeginDrawing();
		
		GameStatesDrawing(gameState);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
}
