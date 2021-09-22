#include "RollADice.h"

namespace game = RuntimeManagement;


namespace RollADice
{
	bool printTutorial = true;
	void PlayGame()
	{
		game::errorMessage = "Invalid word or input. Try again!";
		User::currentBetAmm = 0;
		game::previousGameState = game::currentGameState;
		
		system("CLS");
		if (printTutorial)
		{
			PrintInstructions();
			printTutorial = false;

			User::ConfirmInContinuingPlayingCurrentMode("Roll A Dice");


		}

		if (!User::SetABet(game::currentGameMode))
		{
			return;
		}



		system("CLS");
		std::cout << "Write down a number between 1 and 12: ";
		game::errorMessage = "Invalid number (number is not between 1 and 12). Try again!";
		int userInputValue = game::GetConstrainedNumericalUserInput(1, 12);
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

	void PrintInstructions()
	{
		std::cout << "The rules are simple!\n\n" << std::flush;
		system("pause");
		system("CLS");
		std::cout << "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
		std::cout << "If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n" << std::flush;
		system("pause");
		system("CLS");
	}

	int GenerateResult()
	{
		int firstRoll = rand() % 6 + 1;
		int secondRoll = rand() % 6 + 1;
		return firstRoll + secondRoll;
	}
}


