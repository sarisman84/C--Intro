#pragma once
#include "RuntimeManager.h"
namespace User
{
	extern int currentCapitalAmm;
	extern int currentBetAmm;
	extern bool hasUserWon;

	bool IsBetAmmValid(int aBetAmm);
	void SetABet();
	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName);
	void EarnCapital();
	void PayCapital();
}


