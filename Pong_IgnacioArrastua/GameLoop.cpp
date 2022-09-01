
#include "GameLoop.h"
#include "Pad.h"
#include <cmath>
#include "PowerUp.h"
#include <string>

#include "GameStates.h"

extern GameStates gameState;
Player player[2];
Player extraPads[2];
Ball ball;
PowerUp deadBall;
PowerUp smallPad;
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
	{
		MovePad(player[0], false);
	
	}
	if (gameState != GameStates::VsCpu)
	{
		if (IsKeyDown(KEY_UP) && player[1].pad.y > 1)
		{
			MovePad(player[1], true);
		
		}
		if (IsKeyDown(KEY_DOWN) && player[1].pad.y < maxScreen)
		{
			MovePad(player[1], false);
		
		}
	}

	if (IsKeyReleased(KEY_ESCAPE))
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
	if (isPaused && IsKeyReleased(KEY_SPACE))
	{
		gameState = GameStates::MainMenu;
	}
	if (!isGameRunning &&(IsKeyReleased( KEY_SPACE)))
	{
		gameState = GameStates::MainMenu;
	}
	

}
void DrawGame()
{
	ClearBackground(BLACK);
	int fontSize = 5 * GetScreenWidth() / 190;
	int relativePosP1 = -fontSize - 10;
	int relativePosP2 = -fontSize / 10 + GetScreenWidth() / 150;
	DrawFPS(screenWidth - 80, 10);
	DrawLineBezier({ GetScreenWidth() / 2.0f, 0 }, { GetScreenWidth() / 2.0f,(float)GetScreenHeight() }, 4, GRAY);
	DrawText(TextFormat("%02i", player[0].score), (GetScreenWidth() / 2) + relativePosP1, 0, fontSize, RED);
	DrawText(TextFormat("%02i", player[1].score), GetScreenWidth() / 2 + relativePosP2, 0, fontSize, BLUE);
	DrawPad(player[0]);
	DrawRectangleLinesEx(player[0].pad, 5, RED);
	DrawPad(player[1]);
	DrawRectangleLinesEx(player[1].pad, 5, BLUE);
	drawBall();
	if (deadBall.isSpawned)
	{
		DrawPowerUp(deadBall);
	}
	if (smallPad.isSpawned)
	{
		DrawPowerUp(smallPad);
	}
	


	if (isPaused)
	{
		DrawRectangle(GetScreenWidth() / 4, GetScreenHeight() / 3, GetScreenWidth() / 2, GetScreenHeight() / 4, BLUE);
		std::string pauseTitle = "PAUSE MENU";
		std::string pauseSubtitle = TextFormat("Press the ESC to play");
		std::string pauseSubtitle2 = TextFormat("Press SPACE to go back to menu");
		DrawText(pauseTitle.c_str(), (GetScreenWidth() / 3) + pauseTitle.length() * fontSize / 3, GetScreenHeight() / 3, fontSize, BLACK);
		DrawText(pauseSubtitle.c_str(), (GetScreenWidth() / 4) + pauseSubtitle.length() * fontSize / (pauseSubtitle.length() / 2), GetScreenHeight() / 2.5f, fontSize, BLACK);
		DrawText(pauseSubtitle2.c_str(), (GetScreenWidth() / 4) + pauseSubtitle2.length() * fontSize / (pauseSubtitle2.length() / 2), GetScreenHeight() / 2.2f, fontSize, BLACK);
	}
	if(!isGameRunning)
	{
		std::string Winner = TextFormat("Player %i won!", WinCondition(5));
		std::string WinnerSubtitle = TextFormat("Press SPACE to return to Menu", WinCondition(5));
		DrawText(Winner.c_str(), (GetScreenWidth() / 3) + Winner.length() , GetScreenHeight() / 3, fontSize, GREEN);
		DrawText(WinnerSubtitle.c_str(), (GetScreenWidth() / 4) + WinnerSubtitle.length() * fontSize / (WinnerSubtitle.length() / 2), GetScreenHeight() / 2.5f, fontSize, GREEN);
	}



}

void WallCollision()
{
	if (!deadBall.isActive)
	{
		if (ball.position.x >= (GetScreenWidth() - ball.radius))
		{
			player[0].score++;
			ResetAfterScore();
		}
		if (ball.position.x <= ball.radius)
		{
			player[1].score++;
			ResetAfterScore();
		}
	}
	else if (deadBall.isActive)
	{
		if (ball.position.x >= (GetScreenWidth() - ball.radius) || ball.position.x <= ball.radius)
		{
			ball.speed.x *= -1.0f;
		}
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



bool RectangleCircleCollision(Rectangle powerUp)
{
	float testX = ball.position.x;
	float testY = ball.position.y;

	if (ball.position.x < powerUp.x)
	{
		testX = powerUp.x;
	}
	else if (ball.position.x > powerUp.x + powerUp.width)
	{
		testX = powerUp.x + powerUp.width;
	}
	if (ball.position.y < powerUp.y)
	{
		testY = powerUp.y;
	}
	else if (ball.position.y > powerUp.y + powerUp.height)
	{
		testY = powerUp.y + powerUp.height;
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
bool RectangleCircleCollision(Player player)
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

int WinCondition(int maxScore)
{
	if (player[0].score == maxScore)
	{
		return 1;
	}
	else if (player[1].score == maxScore)
	{
		return 2;
	}
	return 0;
}
void inputIA()
{
	UpdatePadParts(player[1]);
	if (!deadBall.isActive)
	{
		if (player[1].middlePoint > ball.position.y && player[1].pad.y > 1)
		{
			MovePad(player[1], true);
			
		}
		else if (player[1].middlePoint < ball.position.y && player[1].pad.y < GetScreenHeight() - player[1].pad.height)
		{
			MovePad(player[1], false);

			

		}
	}
	else if (deadBall.isActive)
	{
		if (player[1].middlePoint > ball.position.y && player[1].pad.y < GetScreenHeight() - player[1].pad.height)
		{
			MovePad(player[1], false);
			
		}
		else if (player[1].middlePoint < ball.position.y && player[1].pad.y > 1)
		{
			MovePad(player[1], true);
		
		}
	}

}
void InitGame()
{
	SetExitKey(NULL);
	isPaused = false;
	isGameRunning = true;
	deadBall = CreatePowerUp(10, 15);
	smallPad = CreatePowerUp(5,10);

	isGameRunning = true;
	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
	ball = initBall(ballPosition);
	resetBall();
	player[0].pad = createPad(0, GetScreenHeight() / 2, GetScreenHeight() / 40, GetScreenWidth() / 10);
	player[1].pad = createPad(GetScreenWidth(), GetScreenHeight() / 2, GetScreenHeight() / 40, GetScreenWidth() / 10);
	player[0].pad.x = player[0].pad.x  +player[0].pad.width;
	player[1].pad.x = player[1].pad.x  -player[1].pad.width;
	player[0].score = 0;
	player[1].score = 0;
}
void SmallPadLogic()
{
	if (!smallPad.isSpawned && !smallPad.isActive)
	{
		smallPad.timer -= GetFrameTime();
		if (smallPad.timer < 0)
		{
			RandomSpawn(smallPad,YELLOW,smallPad.timer,smallPad.timerActive);
		}
	}
	if (smallPad.isSpawned)
	{
		PowerUpCollision();
	}
	if (smallPad.isActive)
	{
		smallPad.timerActive -= GetFrameTime();
		if (smallPad.timerActive < 0)
		{
			smallPad.isActive = false;
			RestorePaddle();
			smallPad.timer = 45.0f;
		}
	}
}
void powerUpDecreasePaddle()
{
	    player[0].pad.height=  GetScreenWidth() / 20;
		player[1].pad.height=  GetScreenWidth() / 20;
}
void RestorePaddle()
{
	player[0].pad.height = GetScreenWidth() / 10;
	player[1].pad.height = GetScreenWidth() / 10;
}
void ResetPowerUps()
{
	deadBall = CreatePowerUp(30, 15);
	smallPad = CreatePowerUp(20, 10);
	SetPowerUpTimer(smallPad, 25);
}
void ResetAfterScore()
{

	RestorePaddle();
	resetBall();
	ResetPowerUps();
}

void PadCollision()
{
	

	if (RectangleCircleCollision(player[0]))
	{
		UpdatePadParts(player[0]);
		if (!deadBall.isActive)
		{
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
			
			ball.speed.x *= -1.1f;
		}
		else if (deadBall.isActive)
		{
			player[1].score++;
			ResetAfterScore();
		}

	}

	if (RectangleCircleCollision(player[1]))
	{
		UpdatePadParts(player[1]);
		if (!deadBall.isActive)
		{
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
		}
		else if (deadBall.isActive)
		{
			player[0].score++;
			ResetAfterScore();
		}
	}

}
void DeadBallLogic()
{
	if (!deadBall.isSpawned && !deadBall.isActive)
	{
		deadBall.timer -= GetFrameTime();
		if (deadBall.timer < 0)
		{
			RandomSpawn(deadBall,VIOLET,deadBall.timer,deadBall.timerActive);
		}
	}
	if (deadBall.isSpawned)
	{
		PowerUpCollision();
	}
	if (deadBall.isActive)
	{
		ball.color = deadBall.color;
		deadBall.timerActive -= GetFrameTime();
		if (deadBall.timerActive < 0)
		{
			deadBall.isActive = false;
			deadBall.timer = 45.0f;
			ball.color = RAYWHITE;
		}
	}
}
void PowerUpCollision()
{
	if (RectangleCircleCollision(deadBall.rec))
	{
		deadBall.isSpawned = false;
		deadBall.isActive = true;
		ball.color = deadBall.color;
		deadBall.timerActive = 15.0f;
	}
	if (RectangleCircleCollision(smallPad.rec))
	{
		smallPad.isSpawned = false;
		smallPad.isActive = true;
		powerUpDecreasePaddle();
		smallPad.timerActive = 20.0f;
	}
}
void GameLogic()
{
Input();
	if (isGameRunning)
	{
		
		if (!isPaused)
		{
			if (gameState == GameStates::VsCpu)
			{
				inputIA();
			}
			DeadBallLogic();
			SmallPadLogic();
			movePositionBall();
			TopFloorCollision();
			WallCollision();
			PadCollision();
		}

	}

	if (WinCondition(5)>0)
	{
		isGameRunning = false;
		
	}



}