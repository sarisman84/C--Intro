#include "StatisticsManager.h"

namespace game = RuntimeManagement;

namespace Statistics
{
	const int statisticListSize = 5;

	std::array<int, statisticListSize> registeredUserCapital = { 0,0,0,0,0 };
	std::array<int, statisticListSize> registeredUserEarnings = { 0,0,0,0,0 };
	std::array<int, statisticListSize> registedGameCompletions = { 0,0,0,0,0 };

	void SaveCurrentGameStatistics()
	{
		int latestUserCapital = User::currentCapitalAmm;
		int latestUserBet = User::currentBetAmm;

		game::GameMode latestGameMode = game::currentGameMode;

		game::GameState latestGameState = game::currentGameState;


		for (int i = statisticListSize - 1; i > 0; i--)
		{
			int iNext = i - 1;
			

			if (iNext >= 0)
			{
				registedGameCompletions[i] = registedGameCompletions[iNext];
				registeredUserCapital[i] = registeredUserCapital[iNext];
				registeredUserEarnings[i] = registeredUserEarnings[iNext];
			}
		}

		int isGameCompleted = User::hasUserWon ? 1 : -1;
		registedGameCompletions[0] = isGameCompleted;

		registeredUserCapital[0] = User::currentCapitalAmm;
		registeredUserEarnings[0] =
			registedGameCompletions[0] == 1 ?
			latestUserBet * game::CurrentGameModeEarningsMultiplier() : latestUserBet;


	}

	void PrintCurrentStatistics()
	{
		std::cout << "You have thus far:" << std::endl;
		std::cout << "----------------------------------" << std::endl;
		for (int i = 0; i < statisticListSize; i++)
		{
			if (registedGameCompletions[i] != 0 && registeredUserCapital[i] != 0 && registeredUserEarnings[i] != 0)
			{
				bool hasPlayerWon = registedGameCompletions[i] == 1;
				std::cout << "[" << i + 1 << "]Game:" << (hasPlayerWon ? "Won" : "Lost") << ". Capital " << (hasPlayerWon ? "Earned" : "Lost") << ": " << registeredUserEarnings[i] << ". Remaining Capital: " << registeredUserCapital[i] << std::endl;
			}

		}
		std::cout << "----------------------------------" << std::endl;
	}

}