#pragma once
#include "Player.h"

namespace Roullete
{
	enum class BetType
	{
		Straight,
		Split,
		Corner,
		OddOrEven,
		Column,
		RedOrBlack
	};


	void PlayGame();
	extern std::array<std::string, 20> userInstructions;
	bool TryGuessANumber();
	bool TrySelectBetType(BetType &aValidBetType);
}