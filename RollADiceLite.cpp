#include "RollADiceLite.h"

namespace game = RuntimeManagement;

namespace RollADiceLite
{
	const int instructionArraySize = 3;
	const int minDiceRoll = 1, maxDiceRoll = 64;
	const int maxAttempts = 5;
	const int invalidUserInput = -2;

	void GetInstructions(std::string(&anArrayOfInstructions)[instructionArraySize])
	{
		anArrayOfInstructions[0] = "The rules are simple!\n\n";
		anArrayOfInstructions[1] = "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
		anArrayOfInstructions[2] = "If you have failed to guess what number it is, you have 5 more chances to guess again before loosing. We will tell you know close you are! \n\n";
	}

	void PlayGame()
	{
		User::hasUserWon = false;
		game::errorMessage = "Invalid word or input. Try again!";
		User::currentBetAmm = 0;

		if (!User::TrySetABet(game::currentGameMode))
		{
			return;
		}

		system("CLS");

		int attempts = 0;
		int generatedValue;
		generatedValue = GenerateResult();
		game::currentGameState = game::GameState::Lost;
		while (attempts <= maxAttempts)
		{
			std::cout << "Write down a number between 1 and 128: ";
			int userInputValue = User::GetConstrainedNumericalUserInput(minDiceRoll, maxDiceRoll + maxDiceRoll);
			

			if (userInputValue == invalidUserInput)
			{
				system("CLS");
				game::errorMessage = "Inputed value is not between 1 and 128! Try again!";
				game::currentGameState = game::GameState::Error;
				return;
			}
		
			if (generatedValue == userInputValue)
			{
				game::currentGameState = game::GameState::Won;
				break;
			}
			else if (generatedValue < userInputValue)
			{
				std::cout << "Lower!" << std::endl;
				attempts++;
			}
			else if (generatedValue > userInputValue)
			{
				std::cout << "Higher!" << std::endl;
				attempts++;
			}

		}




	}

	int GenerateResult()
	{
		int firstRoll = game::RandomNumber(minDiceRoll, maxDiceRoll);
		int secondRoll = game::RandomNumber(minDiceRoll, maxDiceRoll);
		return firstRoll + secondRoll;
	}
}