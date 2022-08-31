#include "Ball.h"

Ball InitBall(Vector2 screen)
{
	Ball ball =
	{
		screen,GetScreenHeight()/50,minSpeed,minSpeed,RED
	};
	return ball;
}
void MovePositionBall()
{
	if (ball.speed.x > maxSpeed)
	{				   
		ball.speed.x = maxSpeed;
	}
	if (ball.speed.y > maxSpeed)
	{
		ball.speed.y = maxSpeed;
	}
	ball.position.x += ball.speed.x * GetFrameTime();
	ball.position.y += ball.speed.y * GetFrameTime();

}
void ResetPositionBall()
{
	ball.position.x = GetScreenWidth() /2;
	ball.position.y = GetScreenHeight()/2;
	if (GetRandomValue(0,1)==1)
	{
		ball.speed.y = minSpeed;
	}
	else
	{
		ball.speed.y = -minSpeed;
	}
	if (GetRandomValue(0,1)==1)
	{
		ball.speed.x = minSpeed;
	}
	else
	{
		ball.speed.x = -minSpeed;
	}
}
void DrawBall()
{
	DrawCircleV(ball.position, ball.radius, ball.color);
}

