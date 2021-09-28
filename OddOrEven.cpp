#include "OddOrEven.h"


namespace game = RuntimeManagement;

namespace OddOrEven
{

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
		std::cout << "Guess whenever both dice rolls are even or odd: ";
		game::errorMessage = "Invalid guess. Try again!";
		Outcome guessedOutcome = GetOutcomeFromInput();

		if (guessedOutcome == Outcome::Invalid)
		{
			game::currentGameState = game::GameState::Error;
			return;
		}
		system("CLS");
		int firstDiceResult;
		int secondDiceResult;
		bool result = AreDiceRollsGuessedCorrecly(guessedOutcome, firstDiceResult, secondDiceResult);
		std::string printedResult = (result ? "Guessed correctly!" : "Guessed wrong!");
		std::cout << printedResult << " Both dice rolls are " << (result ? "" : "not ") << (guessedOutcome == Outcome::Even ? "even" : "odd") << "!" << std::endl;
		std::cout << "1st Dice: " << firstDiceResult << std::endl;
		std::cout << "2nd Dice: " << secondDiceResult << std::endl << std::endl;

		game::currentGameState = result ? game::GameState::Won : game::GameState::Lost;
	}


	Outcome GetOutcomeFromInput()
	{
		std::string acceptableTerms[] = { "even", "odd" };
		std::string userInput = User::GetUserInput(acceptableTerms, 2);

		if (userInput == "NaN")
		{
			return Outcome::Invalid;
		}


		return  userInput == "even" ? Outcome::Even : userInput == "odd" ? Outcome::Odd : Outcome::Invalid;


	}


	void GetInstructions(std::string(&anArray)[2])
	{
		anArray[0] = "The rules are simple!\n";
		anArray[1] = "Simply write whenever or not the two dice rolls that were thrown are both even or odd!\n";


	}

	bool AreDiceRollsGuessedCorrecly(Outcome someGuessAtAnOverallOutcome, int& aFirstDiceOutcome, int& aSecondDiceOutcome)
	{
		int diceRoll1 = game::RandomNumber(1, 6);
		int diceRoll2 = game::RandomNumber(1, 6);
		aFirstDiceOutcome = diceRoll1;
		aSecondDiceOutcome = diceRoll2;


		switch (someGuessAtAnOverallOutcome)
		{
			case Outcome::Even:
				{

					return diceRoll1 % 2 == 0 && diceRoll2 % 2 == 0;
				}

			case Outcome::Odd:
				{

					return diceRoll1 % 2 != 0 && diceRoll2 % 2 != 0;
				}


		}
		return false;

	}
}