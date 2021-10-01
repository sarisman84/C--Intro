#pragma once
#include "Player.h"

namespace GuessADoor
{



	void DrawDoor(int aDoorIndex, bool aEnterSkip);
	void PlayGame();
	int GenerateResults();
	std::string DrawDoorSymbols(int aDoorIndex, int aMiddlePointOfDoor, std::string aLeftSideSpacing, std::string aRightSideSpacing);
	extern std::array<std::string, 20> userInstructions;

}