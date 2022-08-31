#pragma once
#include "raylib.h"
#include "Ball.h"
#include "Pad.h"

const int screenHeight = 720;
const int screenWidth = 1280;
void Input();
void DrawGame();
void TopFloorCollision();
void PadCollision( );
bool PaddleBallCollision(Player player);
void GameLogic();
bool WinCondition(int maxScore);
void InitGame( );
void DrawGame3D();