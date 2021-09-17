#include "Utility.h"

namespace RuntimeManagement
{
	 //The below variables NEED to be defined for the compiler to work.
	 //Source: https://stackoverflow.com/a/9702142/10483209

	 GameState currentGameState = GameState::Start;
	 GameState previousGameState = currentGameState;
	 GameMode currentGameMode = GameMode::RollADice;
	 const char* errorMessage = "Invalid Input";
	 const char* currentGameModeName = "NaN";

	int GetUserInput(int aMinInputValue, int aMaxInputValue)
	{
		int userInput;
		std::cin >> userInput;
		if (userInput < aMinInputValue || userInput > aMaxInputValue || std::cin.fail())
		{
			userInput = -200;
			std::cin.clear(); //Clears the stream buffer.
			std::cin.ignore(1000); //Clears the input field.
		}

		return userInput;
	}

	GameState GetGameStateFromInput(int someUserInput)
	{
		return static_cast<GameState>(someUserInput);
	}



}


