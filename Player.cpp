#include "Player.h"

namespace game = RuntimeManagement;

namespace User
{
	int currentCapitalAmm = 0;
	int currentBetAmm = 0;
	std::string introductionMessage = "";
	bool hasUserWon = false;

	bool IsBetAmmValid(int aBetAmm)
	{
		return aBetAmm > 1;
	}


	void SetABet()
	{
		system("CLS"); 
		std::cout << "Current amount of cash: " << currentCapitalAmm << "\n";
		std::cout << "Bet an amount of cash: ";
		int userAssignedAmm;
		std::cin >> userAssignedAmm;
		if (User::IsBetAmmValid(userAssignedAmm) && !std::cin.fail())
		{
			User::currentBetAmm = userAssignedAmm;
			std::cout << "Assigned bet accepted! -> " << User::currentBetAmm << "\n";
		}
		else
		{
			RuntimeManagement::currentGameState = RuntimeManagement::GameState::Error;
			return;
		}
	}

	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName)
	{
		std::cout << "You are about to play " << aGameModeName << ". Continue? [Yes/No] ";
		std::string contextPhrasesToSelect[] = { "Yes", "No", "yes", "no" };
		std::string userInput = game::GetUserInput(contextPhrasesToSelect, 4);

		if (userInput == "NaN")
		{
			game::currentGameState = game::GameState::Error;
			return;
		}
		else if (userInput == "No" || userInput == "no")
		{
			game::currentGameState = game::GameState::Menu;
			game::currentGameMode = game::GameMode::None;
			system("CLS");
			return;
		}
	}

	void EarnCapital()
	{
		User::currentCapitalAmm += User::currentBetAmm;

		std::cout <<
			"Earned " << User::currentBetAmm << " cash. " << User::currentCapitalAmm << " remain!\n\n";
	}

	void PayCapital()
	{
		User::currentCapitalAmm -= User::currentBetAmm;

		std::cout << "Lost " << User::currentBetAmm << " cash. " << User::currentCapitalAmm << " remain!\n\n";
	}
}