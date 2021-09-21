#include "OddOrEven.h"

namespace OddOrEven
{
	void PlayGame()
	{

	}

	void PrintInstructions()
	{

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