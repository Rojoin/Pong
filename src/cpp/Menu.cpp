#include "Menu.h"

#include <string>

#include "Button.h"
#include "raylib.h"

bool test = false;
std::string creator = "                      Game made by Ignacio 'Rojoin' Arrastua";
Button playVsButton = createButton("VS MODE", WHITE);
Button playVsCpuButton = createButton("  VS CPU", WHITE);
Button screenButton = createButton(" SCREENRES ", WHITE);
Button rulesButton = createButton(" RULES ", WHITE);
Button exitButton = createButton("  EXIT", WHITE);
void MenuState(GameStates& gamestate)
{
	playVsButton = createButton("  VS MODE", WHITE);
	playVsCpuButton = createButton(playVsButton.rec.x, (float)GetScreenHeight() / 4, playVsCpuButton.buttonTittle, playVsCpuButton.color);
	screenButton = createButton(playVsButton.rec.x, (float)GetScreenHeight() / 2- GetScreenHeight() / 11, screenButton.buttonTittle, screenButton.color);
	rulesButton = createButton(playVsButton.rec.x, (float)GetScreenHeight() / 2 , rulesButton.buttonTittle, rulesButton.color);
	exitButton = createButton(playVsButton.rec.x, (float)GetScreenHeight() / 2+ GetScreenHeight() / 4, exitButton.buttonTittle, exitButton.color);
	Vector2 mousePoint = GetMousePosition();

	if (CheckCollisionPointRec(mousePoint, playVsButton.rec))
	{
		playVsButton.isOverThisButton = true;


		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			InitGame();
			gamestate = GameStates::VsPlayer;
		}

	}
	else
	{
		playVsButton.isOverThisButton = false;
	}
	if (CheckCollisionPointRec(mousePoint, playVsCpuButton.rec))
	{
		playVsCpuButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			InitGame();
			gamestate = GameStates::VsCpu;
		}
	}
	else
	{
		playVsCpuButton.isOverThisButton = false;
	}
	if (CheckCollisionPointRec(mousePoint, screenButton.rec))
	{
		screenButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			if (!IsWindowFullscreen())
			{
				SetWindowSize(1920, 1080);
				ToggleFullscreen();

			}
			else
			{
				ToggleFullscreen();
				SetWindowSize(1280, 720);
			}
			
		}
	}
	else
	{
		screenButton.isOverThisButton = false;
	}

	if (CheckCollisionPointRec(mousePoint, rulesButton.rec))
	{
		rulesButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = GameStates::Rules;
		}
	}
	else
	{
		exitButton.isOverThisButton = false;
	}
	if (CheckCollisionPointRec(mousePoint, exitButton.rec))
	{
		exitButton.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			gamestate = GameStates::Exit;
		}
	}
	else
	{
		exitButton.isOverThisButton = false;
	}
	
}
void MenuDraw()
{
	
	ClearBackground(BLACK);
	drawButton(playVsButton);
	drawButton(playVsCpuButton);
	drawButton(screenButton);
	drawButton(rulesButton);
	drawButton(exitButton);
	int fontSize = 3 * GetScreenWidth() / 190;
	DrawText(creator.c_str(), GetScreenWidth()/2+creator.length(), GetScreenHeight() - fontSize, fontSize, RED);
	std::string titleScreen = "Pong";

	DrawText(titleScreen.c_str(), ((GetScreenWidth() / 2) - titleScreen.length()*fontSize), GetScreenHeight() / 8, fontSize*4, RED);
}
