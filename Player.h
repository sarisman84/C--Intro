#pragma once
#include "RuntimeManager.h"
namespace User
{
	extern int currentCapitalAmm;
	extern int currentBetAmm;
	extern bool hasUserWon;

	bool IsBetAmmValid(int aBetAmm);
	bool SetABet(RuntimeManagement::GameMode aCurrentGameMode);
	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName);
	void EarnCapital(RuntimeManagement::GameMode aCurrentGameMode);
	void PayCapital();
	bool HasCapital();
}


