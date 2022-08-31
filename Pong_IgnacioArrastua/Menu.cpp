#include "Menu.h"

#include <string>

#include "Button.h"
#include "raylib.h"

bool test = false;

Button playVsButton = createButton("VS MODE", WHITE);
Button playVsCpu = createButton("  VS CPU", WHITE);
void MenuState(GameStates& gamestate)
{
	playVsButton = createButton("  VS MODE", WHITE);
	playVsCpu = createButton(playVsButton.rec.x, (float)GetScreenHeight() / 4, playVsCpu.buttonTittle, playVsCpu.color);
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
	if (CheckCollisionPointRec(mousePoint, playVsCpu.rec))
	{
		playVsCpu.isOverThisButton = true;
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			InitGame();
			gamestate = GameStates::VsCpu;
		}
	}
	else
	{
		playVsCpu.isOverThisButton = false;
	}



}
void MenuDraw()
{
	//	Rectangle tryButton{ (float)GetScreenWidth() / 2 - 50,(float)GetScreenHeight() / 3,100,50 };

	ClearBackground(BLUE);
	DrawButton(playVsButton);
	DrawButton(playVsCpu);
	std::string titleScreen = "Pong";
	/*DrawRectangleRec(tryButton, GREEN);
	if (test)
	{
		DrawRectangleLinesEx(tryButton, 5, RED);
	}*/
	DrawText(titleScreen.c_str(), ((GetScreenWidth() / 2) - titleScreen.length() - 50), GetScreenHeight() / 8, 50, RED);
}
