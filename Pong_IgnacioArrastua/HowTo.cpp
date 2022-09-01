#include "HowTo.h"
#include "Button.h"

Button escapeButton = createButton("  GO BACK", WHITE);
void RulesStates(GameStates& gamestate)
{
	Vector2 mousePoint = GetMousePosition();
	escapeButton = createButton(escapeButton.rec.x, (float)GetScreenHeight()-escapeButton.rec.height, escapeButton.buttonTittle, escapeButton.color);
	if (CheckCollisionPointRec(mousePoint, escapeButton.rec))
	{
		escapeButton.isOverThisButton = true;


		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			InitGame();
			gamestate = GameStates::MainMenu;
		}

	}
	else
	{
		escapeButton.isOverThisButton = false;
	}
}
void RulesDraw()
{

	ClearBackground(BLACK);
	drawButton(escapeButton);
	std::string rules = "Rules";
	int fontSize = 3 * GetScreenWidth() / 190;
	std::string firstSentence = "Pong is a single and multiplayer game that emulates a PingPong game";
	std::string secondSentence = "The objective is simple,score 5 points to win before your opponent.";
	std::string thirdSentence = "Player 1(At the left) will use W S while Player 2 will use the up and down key.";
	std::string forthSentence = "When the ball turns Violet avoid it or your oponnent will get a point!.";
	std::string fifthSentence = "And watchout, you can get Shrink with the YELLOW powerUp.";

	DrawText(firstSentence.c_str(), GetScreenWidth() / 3-firstSentence.length(), (GetScreenHeight() / 4+ fontSize), fontSize, RAYWHITE);
	DrawText(secondSentence.c_str(), GetScreenWidth() / 3 -secondSentence.length(), (GetScreenHeight()/5 + fontSize), fontSize, RAYWHITE);
	DrawText(thirdSentence.c_str(), GetScreenWidth() / 3-thirdSentence.length(), (GetScreenHeight()/2- GetScreenHeight() / 5) + fontSize, fontSize, RAYWHITE);
	DrawText(forthSentence.c_str(), GetScreenWidth() / 3-forthSentence.length(), (GetScreenHeight()/2- GetScreenHeight() / 6) + fontSize, fontSize, RAYWHITE);
	DrawText(fifthSentence.c_str(), GetScreenWidth() / 3- fifthSentence.length(), (GetScreenHeight()/2- GetScreenHeight() / 7) + fontSize, fontSize, RAYWHITE);
	DrawText(rules.c_str(), ((GetScreenWidth() / 2) - rules.length() * fontSize), GetScreenHeight() / 10, fontSize * 4, RED);

	drawButton(escapeButton);


}
