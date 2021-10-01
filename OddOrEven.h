#pragma once
#include "Player.h";
namespace OddOrEven
{
	/*
	Rules are simple.

	The user chooses either even or odd as a guess

	The computer then rolls two dice. \
	If both dice are of the users desired outcome, say even,
	then the user wins. Otherwise, the user looses.

	*/
	
	

	enum class Outcome
	{
		Odd,
		Even,
		Invalid
	};

	void PlayGame();
	extern std::array<std::string, 20> userInstructions;
	bool AreDiceRollsGuessedCorrecly(Outcome someGuessAtAnOutcome, int& aFirstDiceOutcome, int& aSecondDiceOutcome);
	Outcome GetOutcomeFromInput();
	






}
