#include "Ball.h"

Ball initBall(Vector2 screen)
{
	Ball ball =
	{
		screen,GetScreenHeight()/50,minSpeed,minSpeed,RED
	};
	return ball;
}
void movePositionBall()
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
void resetBall()
{
	ball.position.x = GetScreenWidth() /2;
	ball.position.y = GetScreenHeight()/2;
	ball.color = RAYWHITE;
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
void drawBall()
{
	DrawCircleV(ball.position, ball.radius, ball.color);
}

