#pragma once
#include "RuntimeManager.h"
namespace User
{
	extern int currentCapitalAmm;
	extern int currentBetAmm;
	extern int ammOfWinsInRollADice;
	extern int ammOfWinsInOddOrEven;
	extern int ammOfWinsInThirdGameMode;
	extern bool hasUserWon;

	bool IsBetAmmValid(int aBetAmm);
	bool TrySetABet(RuntimeManagement::GameMode aCurrentGameMode);
	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName);
	void DisplayStringArrayToConsole(int anArraySize, std::string someInstructions[]);
	void EarnCapital();
	int GetConstrainedNumericalUserInput(int aMinInputValue, int aMaxInputValue);
	int GetNumericalUserInput(int someAllowedValues[]);
	std::string GetUserInput(std::string someAcceptablePhrases[], int anArraySize);
	void PayCapital();
	bool HasCapital();
	void IncrementWinCounter();
	void ReduceWinCounter();
	bool HasWonTooManyTimes(int someLimit, RuntimeManagement::GameMode aGameMode);
}


