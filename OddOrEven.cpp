#include "OddOrEven.h"

namespace game = RuntimeManagement;

namespace OddOrEven
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
			
			User::ConfirmInContinuingPlayingCurrentMode("Odd Or Even");


		}

		User::SetABet();

		system("CLS");
		std::cout << "Guess whenever both dice rolls are even or odd: ";
		game::errorMessage = "Invalid guess. Try again!";
		Outcome guessedOutcome = GetOutcomeFromInput();

		if (guessedOutcome == Outcome::Invalid)
		{
			game::currentGameState = game::GameState::Error;
			return;
		}
		system("CLS");

		bool result = AreDiceRollsGuessedCorrecly(guessedOutcome);
		std::string printedResult = (result ? "Guessed correctly!" : "Guessed wrong!");
		std::cout << printedResult << " Both dice rolls are "<< (result ? "" : "not ") << (guessedOutcome == Outcome::Even ? "even" : "odd") << "!" << std::endl;
		
		game::currentGameState = result ? game::GameState::Won : game::GameState::Lost;
	}	
	

	Outcome GetOutcomeFromInput()
	{
		std::string acceptableTerms[] = { "Even", "even", "Odd", "odd" };
		std::string userInput = game::GetUserInput(acceptableTerms, 4);

		if (userInput == "NaN")
		{
			return Outcome::Invalid;
		}

	
		return userInput == "Even" || userInput == "even" ? Outcome::Even : userInput == "Odd" || userInput == "odd" ? Outcome::Odd : Outcome::Invalid;


	}

	void PrintInstructions()
	{
		system("CLS");
		std::cout << "The rules are simple!\n\n" << std::flush;
		system("pause");
		system("CLS");
		std::cout << "Simply write whenever or not the two dice rolls that were thrown are both even or odd!\n\n";
		system("pause");
		system("CLS");
	}

	bool AreDiceRollsGuessedCorrecly(Outcome someGuessAtAnOutcome)
	{
		int diceRoll1 = rand() % 6 + 1;
		int diceRoll2 = rand() % 6 + 1;


		switch (someGuessAtAnOutcome)
		{
			case Outcome::Even:
				return diceRoll1 % 2 == 0 && diceRoll2 % 2 == 0;
			case Outcome::Odd:
				return diceRoll1 % 2 != 0 && diceRoll2 % 2 != 0;

		}
		return false;

	}
}