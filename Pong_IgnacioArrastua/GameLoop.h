#pragma once
#include "raylib.h"
#include "Ball.h"
#include "Pad.h"

const int screenHeight = 720;
const int screenWidth = 1280;
void Input();
void DrawGame();
void WallCollision();
void TopFloorCollision();

void PadCollision( );
bool RectangleCircleCollision(Player player);
bool RectangleCircleCollision(Rectangle powerUp);
void GameLogic();
int WinCondition(int maxScore);
void InitGame( );
void PowerUpCollision();
void RestorePaddle();
void ResetAfterScore();
void ResetPowerUps();