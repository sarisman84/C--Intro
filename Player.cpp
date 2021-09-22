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
		return aBetAmm > 1 && aBetAmm <= currentCapitalAmm;
	}

	bool HasCapital()
	{
		return currentCapitalAmm > 0;
	}


	bool SetABet(game::GameMode aCurrentGameMode)
	{
		system("CLS");
		std::cout << "Current amount of cash: " << currentCapitalAmm << "\n";

		std::string multiplierOutput;

		switch (aCurrentGameMode)
		{

			case RuntimeManagement::GameMode::RollADice:
				{
					multiplierOutput = "[x2]";
					break;
				}


			case RuntimeManagement::GameMode::OddOrEven:
				{
					multiplierOutput = "[x3]";
					break;
				}


		}

		std::cout << "Bet an amount of cash (" << multiplierOutput << "cash amount upon winning!):";
		int userAssignedAmm;
		std::cin >> userAssignedAmm;
		if (User::IsBetAmmValid(userAssignedAmm) && !std::cin.fail())
		{
			User::currentBetAmm = userAssignedAmm;
			std::cout << "Assigned bet accepted! -> " << User::currentBetAmm << " (" << multiplierOutput << "cash amount upon winning!)\n";
				system("pause");
			return true;
		}
		else
		{
			game::errorMessage = "Invalid bet amount! Try again!";
			game::currentGameState = game::GameState::Error;
			return false;
		}
		return false;
	}

	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName)
	{
		std::cout << "You are about to play " << aGameModeName << ". Continue? [Yes/No] ";
		std::string contextPhrasesToSelect[] = { "yes", "no" };
		std::string userInput = game::GetUserInput(contextPhrasesToSelect, 4);

		if (userInput == "NaN")
		{
			game::currentGameState = game::GameState::Error;
			return;
		}
		else if (userInput == "no")
		{
			game::currentGameState = game::GameState::Menu;
			game::currentGameMode = game::GameMode::None;
			system("CLS");
			return;
		}
	}

	void EarnCapital(game::GameMode aCurrentGameMode)
	{
		switch (aCurrentGameMode)
		{

			case RuntimeManagement::GameMode::RollADice:
				{
					User::currentCapitalAmm += User::currentBetAmm * 2;
					break;
				}

			case RuntimeManagement::GameMode::OddOrEven:
				{
					User::currentCapitalAmm += User::currentBetAmm * 3;
					break;
				}


		}


		std::cout <<
			"Earned " << User::currentBetAmm * 2 << " cash. " << User::currentCapitalAmm << " remain!\n\n";
	}

	void PayCapital()
	{
		User::currentCapitalAmm -= User::currentBetAmm;

		std::cout << "Lost " << User::currentBetAmm << " cash. " << User::currentCapitalAmm << " remain!\n\n";
	}
}