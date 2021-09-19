#include "RollADice.h"

namespace game = RuntimeManagement;

namespace RollADice
{
	bool printTutorial = true;
	void PlayGame()
	{
		game::previousGameState = game::currentGameState;
		std::string introductionMessage = "You are about to play Roll a Dice! Continue?(Yes to continue, No to go back to the menu)\n";
		system("CLS");
		if (printTutorial)
		{
			PrintInstructions();
			printTutorial = false;

			std::cout << introductionMessage;
			std::string contextPhrasesToSelect[] = { "Yes", "No", "yes", "no"};
			std::string userInput = game::GetUserInput(contextPhrasesToSelect);

			if (userInput == "NaN")
			{
				game::currentGameState = game::GameState::Error;
				return;
			}
			else if (userInput == "No" || userInput == "no")
			{
				game::currentGameState = game::GameState::Menu;
				game::currentGameMode = game::GameMode::None;
				system("CLS");
				return;
			}
			
			
		}




		std::cout << "Write down a number between 1 and 12: ";

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
		game::currentGameState = userInputValue == generatedValue ? game::GameState::Won : game::GameState::Lost;
		system("CLS");
		std::cout << "The dice yielded " << generatedValue << ", making " << userInputValue << (userInputValue == generatedValue ? " equal " : " not equal ") << "to " << generatedValue << "!\n";

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


