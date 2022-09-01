#include "PowerUp.h"



PowerUp CreatePowerUp(float timer, float timerActive)
{
	PowerUp powerUp;
	float width = GetScreenWidth() / 10;
	float height = GetScreenHeight() / 20;
	powerUp.rec = { (float)GetScreenWidth() / 2 - width / 2, (float)GetScreenHeight() / 3, width, height };
	powerUp.color = VIOLET;
	powerUp.timer = timer;
	powerUp.timerActive = timerActive;
	powerUp.isActive = false;
	powerUp.isSpawned = false;
	return powerUp;
}
void DrawPowerUp(PowerUp powerUp)
{
	DrawRectangleRec(powerUp.rec, powerUp.color);
}
void RandomSpawn(PowerUp& powerUp,Color color,float timer, float timerActive)
{
	int spawn = GetRandomValue(1, 4);
	powerUp = CreatePowerUp(timer,timerActive);
	SetColor(powerUp, color);
	powerUp.isSpawned = true;
	switch (spawn)
	{
	case 1:
		powerUp.rec.x = GetScreenWidth()/4;
		powerUp.rec.y = GetScreenHeight()/4;
		break;
	case 2:
		powerUp.rec.x = GetScreenWidth()/4  ;
		powerUp.rec.y = (GetScreenHeight() / 4) *3;
		break;
	case 3:
		powerUp.rec.x = (GetScreenWidth() / 4)*3;
		powerUp.rec.y = (GetScreenHeight() / 4) * 3;
		break;
	case 4:
		powerUp.rec.x = (GetScreenWidth() / 4 )* 3;
		powerUp.rec.y = (GetScreenHeight() / 4);
		break;
	}
}

void SetPowerUpTimer(PowerUp& powerUp,float timer)
{
	powerUp.timer = timer;
}


void SetColor(PowerUp& powerUp,Color color)
{
	powerUp.color = color;
}

