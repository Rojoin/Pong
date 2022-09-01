#include "Pad.h"

Rectangle createPad(float x, float y, float width, float height)
{

	return Rectangle() = { x,y,width,height};
}

void MovePad(Player& player,bool up)
{
	if (up)
	{
		player.pad.y -= padSpeed* GetFrameTime()*GetScreenHeight()/450;
	}
	else
	{
		player.pad.y += padSpeed * GetFrameTime() * GetScreenHeight() / 450;
	}
}
void DrawPad(Player player)
{
	DrawRectangleRec(player.pad, WHITE);
}

void UpdatePadParts(Player& player)
{
	player.middlePoint = { player.pad.y + (player.pad.height / 2) };
	player.endPoint = { player.pad.y +  player.pad.height };
}