#include "RollADice.h"

namespace game = RuntimeManagement;


namespace RollADice
{

	void PlayGame()
	{
		game::errorMessage = "Invalid word or input. Try again!";
		User::currentBetAmm = 0;

		if (!User::TrySetABet(game::currentGameMode))
		{
			return;
		}



		system("CLS");
		std::cout << "Write down a number between 1 and 12: ";
		game::errorMessage = "Invalid number (number is not between 1 and 12). Try again!";
		int userInputValue = User::GetConstrainedNumericalUserInput(1, 12);
		int generatedValue;

		if (userInputValue == -2)
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



	void GetInstructions(std::string(&anArray)[3])
	{
		anArray[0] = "The rules are simple!\n\n";
		anArray[1] = "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
		anArray[2] = "If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n";
	}

	int GenerateResult()
	{
		int firstRoll = game::RandomNumber(1, 6);
		int secondRoll = game::RandomNumber(1, 6);
		return firstRoll + secondRoll;
	}
}


