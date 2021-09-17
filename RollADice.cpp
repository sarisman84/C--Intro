#include<iostream>
#include "RollADice.h"
#include "Utility.h"


namespace game = RuntimeManagement;

void RollADice::PlayGame()
{
	std::cout << "Write down a number between 1 and 12: ";
	game::previousGameState = game::currentGameState;
	int userInputValue = RuntimeManagement::GetUserInput(1, 12);
	int generatedValue;

	if (userInputValue == -2)
	{
		game::errorMessage = "Inputed value is not between 1 and 12! Try again!";
		game::currentGameState = static_cast<game::GameState>(userInputValue);
		system("CLS");
		return;
	}

	generatedValue = GenerateResult();
	game::currentGameState = userInputValue == generatedValue ? game::GameState::Won : game::GameState::Lost;
	system("CLS");
	std::cout << "The dice yielded " << generatedValue << ", making " << userInputValue << (userInputValue == generatedValue ? " equal " : " not equal ") << "to " << generatedValue << "!\n";
}

void RollADice::PrintInstructions()
{
}

int RollADice::GenerateResult()
{
	int firstRoll = rand() % 6 + 1;
	int secondRoll = rand() % 6 + 1;
	return firstRoll + secondRoll;
}
