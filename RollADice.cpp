#include "RollADice.h"

namespace game = RuntimeManagement;


namespace RollADice
{
	const int instructionArraySize = 3;
	const int minDiceRoll = 1, maxDiceRoll = 6;
	const int invalidUserInput = -2;
	std::array<std::string, 20> userInstructions = {
		"The rules are simple!\n\n",
		"Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown between " + std::to_string(minDiceRoll) + " and " + std::to_string(maxDiceRoll) + "! \n",
		"If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n"
	};


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
		std::cout << "Write down a number between 1 and 12: ";
		game::errorMessage = "Invalid number (number is not between 1 and 12). Try again!";
		int userInputValue = User::GetConstrainedNumericalUserInput(minDiceRoll, maxDiceRoll + maxDiceRoll);
		int generatedValue;

		if (userInputValue == invalidUserInput)
		{
			game::errorMessage = "Inputed value is not between 1 and 12! Try again!";
			game::currentGameState = static_cast<game::GameState>(userInputValue);
			system("CLS");
			return;
		}

		generatedValue = GenerateResult();

		User::hasUserWon = userInputValue == generatedValue;
		game::currentGameState = User::hasUserWon ? game::GameState::Won : game::GameState::Lost;
		system("CLS");
		std::cout << "The dice yielded " << generatedValue << ", making " << userInputValue << (User::hasUserWon ? " equal " : " not equal ") << "to " << generatedValue << "!\n\n";




	}





	int GenerateResult()
	{
		int firstRoll = game::RandomNumber(minDiceRoll, maxDiceRoll);
		int secondRoll = game::RandomNumber(minDiceRoll, maxDiceRoll);
		return firstRoll + secondRoll;
	}


}


