#include "OddOrEven.h"


namespace game = RuntimeManagement;

namespace OddOrEven
{
	const int instructionArraySize = 2;
	const int minDiceRoll = 1, maxDiceRoll = 6;
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
		std::cout << "1st Dice: " << firstDiceResult << "->" << (firstDiceResult % 2 == 0 ? "Even" : "Odd") << std::endl;
		std::cout << "2nd Dice: " << secondDiceResult << "->" << (secondDiceResult % 2 == 0 ? "Even" : "Odd") << std::endl << std::endl;

		game::currentGameState = result ? game::GameState::Won : game::GameState::Lost;
	}


	Outcome GetOutcomeFromInput()
	{
		const std::string evenOutcome = "even", oddOutcome = "odd";
		const int acceptableTermsSize = 2;
		std::string acceptableTerms[] = { evenOutcome, oddOutcome };
		std::string userInput = User::GetUserInput(acceptableTerms, acceptableTermsSize);

		if (userInput == User::invalidInput)
		{
			return Outcome::Invalid;
		}


		return  userInput == evenOutcome ? Outcome::Even : userInput == oddOutcome ? Outcome::Odd : Outcome::Invalid;


	}


	void GetInstructions(std::string(&anArray)[instructionArraySize])
	{
		anArray[0] = "The rules are simple!\n";
		anArray[1] = "Simply write whenever or not the two dice rolls that were thrown are both even or odd!\n";


	}

	bool AreDiceRollsGuessedCorrecly(Outcome someGuessAtAnOverallOutcome, int& aFirstDiceOutcome, int& aSecondDiceOutcome)
	{
		int diceRoll1 = game::RandomNumber(minDiceRoll, maxDiceRoll);
		int diceRoll2 = game::RandomNumber(minDiceRoll, maxDiceRoll);
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