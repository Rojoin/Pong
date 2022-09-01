#pragma once
#include "raylib.h"

const float minSpeed = 300.0f;
const float maxSpeed = 1000.0f;
struct Ball
{
	Vector2 position = {};
	int radius = { 5 };
	Vector2 speed = { 3.0f,3.0f };
	Color color = RED;
};
 extern Ball ball;


Ball initBall(Vector2 screen);
void movePositionBall();
void resetBall();
void drawBall();

