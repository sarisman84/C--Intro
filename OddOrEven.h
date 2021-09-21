#pragma once
#include "RollADice.h";
namespace OddOrEven
{
	/*
	Rules are simple.

	The user chooses either even or odd as a guess

	The computer then rolls two dice. \
	If both dice are of the users desired outcome, say even,
	then the user wins. Otherwise, the user looses.
	
	*/

	void PlayGame();
	void PrintInstructions();
	bool AreDiceRollsGuessedCorrecly(Outcome someGuessAtAnOutcome);

	enum class Outcome
	{
		Odd,
		Even
	};
	
}
