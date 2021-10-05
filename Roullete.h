#pragma once
#include "Player.h"

namespace Roulette
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
	bool TryGuessASplit();
	bool TrySelectBetType(BetType &aValidBetType);
	int GetValidatedNumberThatIsAdjacent(int anOriginPoint, int aNewNumber);
	int GetBetMultiplier();
}