#pragma once
#include <raylib.h>

struct PowerUp
{

	Rectangle rec;
	Color color;
	float timer;
	float timerActive;
	bool isActive;
	bool isSpawned;

};

PowerUp CreatePowerUp(float timer, float timerActive);
void RandomSpawn(PowerUp& powerUp, Color color, float timer, float timerActive);
void SetPowerUpTimer(PowerUp& powerUp, float timer);
void SetColor(PowerUp& ,Color color);
void DrawPowerUp(PowerUp powerUp);