#pragma once
#include "raylib.h"

static float padSpeed = 400.0f;
struct Player
{
	Rectangle pad;
	float middlePoint;
	float endPoint;
	int score;
};
extern Player player[2];
Rectangle createPad(float x, float y, float width, float height);
void MovePad(Player& rec,bool up);
void DrawPad(Player rec);
void UpdatePadParts(Player& player);

