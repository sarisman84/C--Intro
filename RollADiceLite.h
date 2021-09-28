#pragma once
#include "RollADice.h"

namespace RollADiceLite
{
	void GetInstructions(std::string(&anArrayOfInstructions)[3]);
	void PlayGame();
	int GenerateResult();
}
