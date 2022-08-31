
#include "GameLoop.h"
#include "Pad.h"
#include <cmath>
#include <ctime>
#include <string>

#include "GameStates.h"

extern GameStates gameState;
Player player[2];
Ball ball;
static bool isPaused = false;
static bool isGameRunning = true;
void Input()
{
	int maxScreen = GetScreenHeight() - player[0].pad.height;
	if (IsKeyDown(KEY_W) && player[0].pad.y > 1)
	{
		MovePad(player[0], true);

	}
	if (IsKeyDown(KEY_S) && player[0].pad.y < maxScreen)
		MovePad(player[0], false);
	if (IsKeyDown(KEY_UP) && player[1].pad.y > 1)MovePad(player[1], true);
	if (IsKeyDown(KEY_DOWN) && player[1].pad.y < maxScreen)
		MovePad(player[1], false);

	if (IsKeyReleased(KEY_P))
		{
			if (!isPaused)
			{
				isPaused = true;
			}
			else
			{
				isPaused = false;
			}
		}
}
void DrawGame()
{
	ClearBackground(BLACK);
		int fontSize = 5 * GetScreenWidth() / 190;
		int relativePosP1 = -fontSize - 10;
		int relativePosP2 = -fontSize / 10 + GetScreenWidth() / 150;
		DrawFPS(screenWidth - 80, 10);
		DrawLineBezier({ GetScreenWidth() / 2.0f, 0 }, { GetScreenWidth() / 2.0f,(float)GetScreenHeight() }, 4, DARKBLUE);
		DrawText(TextFormat("%02i", player[0].score), (GetScreenWidth() / 2) + relativePosP1, 0, fontSize, RED);
		DrawText(TextFormat("%02i", player[1].score), GetScreenWidth() / 2 + relativePosP2, 0, fontSize, RED);
		DrawPad(player[0]);
		DrawRectangleLinesEx(player[0].pad, 5, RED);
		DrawPad(player[1]);
		DrawRectangleLinesEx(player[1].pad, 5, RED);
		DrawBall();

	if (isPaused)
	{
		DrawRectangle(GetScreenWidth() / 4, GetScreenHeight() / 3, GetScreenWidth() / 2, GetScreenHeight() / 4, BLUE);
		std::string pauseTitle = "PAUSE MENU";
		std::string pauseSubtitle = TextFormat("Press the pause key to play");
		std::string pauseSubtitle2 = TextFormat("Press ESC to go back to menu");
		DrawText(pauseTitle.c_str(), (GetScreenWidth() / 3)+pauseTitle.length()*fontSize/3, GetScreenHeight() / 3, fontSize, BLACK);
		DrawText(pauseSubtitle.c_str(), (GetScreenWidth() / 4)+pauseSubtitle.length()*fontSize/(pauseSubtitle.length()/2), GetScreenHeight() / 2.5f, fontSize, BLACK);
		DrawText(pauseSubtitle2.c_str(), (GetScreenWidth() / 4)+pauseSubtitle2.length()*fontSize/(pauseSubtitle2.length()/2), GetScreenHeight() / 2.2f, fontSize, BLACK);
	}

	


}

void WallCollision()
{
	if (ball.position.x >= (GetScreenWidth() - ball.radius))
	{
		player[0].score++;
		ResetPositionBall();
	}
	if (ball.position.x <= ball.radius)
	{
		player[1].score++;
		ResetPositionBall();
	}

}
void TopFloorCollision()
{
	if (ball.position.y >= (GetScreenHeight() - ball.radius))
	{
		ball.position.y = (GetScreenHeight() - ball.radius) - 0.02f;
		ball.speed.y *= -1.0f;
	}

	if (ball.position.y <= ball.radius)
	{
		ball.position.y += ball.radius + 0.01f;
		ball.speed.y *= -1.0f;
	}
}

bool PaddleBallCollision(Player player)
{
	float testX = ball.position.x;
	float testY = ball.position.y;

	if (ball.position.x < player.pad.x)
	{
		testX = player.pad.x;
	}
	else if (ball.position.x > player.pad.x + player.pad.width)
	{
		testX = player.pad.x + player.pad.width;
	}
	if (ball.position.y < player.pad.y)
	{
		testY = player.pad.y;
	}
	else if (ball.position.y > player.pad.y + player.pad.height)
	{
		testY = player.pad.y + player.pad.height;
	}

	float distanceX = ball.position.x - testX;
	float distanceY = ball.position.y - testY;
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= ball.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool WinCondition(int maxScore)
{
	if (player[0].score == maxScore)
	{
		return true;
	}
	else if (player[1].score == maxScore)
	{
		return true;
	}
	return false;
}
void inputIA()
{
	UpdatePadParts(player[1]);
	if (player[1].middlePoint > ball.position.y && player[1].pad.y > 1)
	{
		MovePad(player[1], true);
	}
	else if (player[1].middlePoint < ball.position.y && player[1].pad.y < GetScreenHeight() - player[1].pad.height)
	{
		MovePad(player[1], false);
	}
}
void InitGame()
{
	isGameRunning = true;
	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	ball = InitBall(ballPosition);
	ResetPositionBall();
	player[0].pad = createPad(10, screenHeight / 2, GetScreenHeight() / 40, GetScreenWidth() / 10);
	player[1].pad = createPad(screenWidth - 30, screenHeight / 2, GetScreenHeight() / 40, GetScreenWidth() / 10);
	player[0].score = 0;
	player[1].score = 0;
}
void PadCollision()
{
	Sound fxButton = LoadSound("Sounds/a.wav");

	if (PaddleBallCollision(player[0]))
	{
		UpdatePadParts(player[0]);

		ball.position.x = player[0].pad.x + player[0].pad.width + ball.radius + 0.1f;
		ball.speed.y = abs(ball.speed.y);

		if (ball.position.y <= player[0].pad.y)
		{
			ball.speed.y *= -1.1f;
		}
		else if (ball.position.y > player[0].pad.y && ball.position.y < player[0].middlePoint)
		{
			ball.speed.y *= -((ball.position.y / player[0].middlePoint) + 0.30f);
		}
		else if (ball.position.y > player[0].middlePoint && ball.position.y < player[0].endPoint)
		{
			ball.speed.y *= (ball.position.y / player[0].endPoint) + 0.30f;
		}
		else if (ball.position.y >= player[0].endPoint)
		{
			ball.speed.y *= 1.1f;
		}
		PlaySound(fxButton);
		ball.speed.x *= -1.1f;

	}

	if (PaddleBallCollision(player[1]))
	{
		UpdatePadParts(player[1]);

		ball.position.x = player[1].pad.x - ball.radius - 0.1f;


		ball.speed.y = abs(ball.speed.y);

		if (ball.position.y <= player[1].pad.y)
		{
			ball.speed.y *= -1.1f;
		}
		else if (ball.position.y > player[1].pad.y && ball.position.y < player[1].middlePoint)
		{
			ball.speed.y *= -((ball.position.y / player[1].middlePoint) + 0.50f);
		}
		else if (ball.position.y > player[1].middlePoint && ball.position.y < player[1].endPoint)
		{
			ball.speed.y *= (ball.position.y / player[1].endPoint) + 0.50f;
		}
		else if (ball.position.y >= player[1].endPoint)
		{
			ball.speed.y *= 1.1f;
		}

		ball.speed.x *= -1.1f;
		PlaySound(fxButton);
	}

}

void GameLogic()
{

	if (isGameRunning)
	{
		Input();
		if (!isPaused)
		{
			inputIA();
			MovePositionBall();
			TopFloorCollision();
			WallCollision();
			PadCollision();
		}

	}

	isGameRunning = !WinCondition(2);
	if (!isGameRunning)
	{
		gameState = GameStates::MainMenu;
	}



}