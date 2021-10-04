#include "Roullete.h"


namespace game = RuntimeManagement;

namespace Roullete
{
	const int roulleteStartingNumber = 0;
	const int roulleteNumberAmm = 36;
	const int roulleteRowAmm = 12;
	const int roulleteCollumAmm = 3;


	std::array<std::string, 20> userInstructions = {

	};

	std::array<std::array < int, 3>, 12> roulleteBoard = { {
		{ 1, 2, 3},
		{ 4, 5, 6},
		{ 7, 8, 9},
		{10,11,12},
		{13,14,15},
		{16,17,18},
		{19,20,21},
		{22,23,24},
		{25,26,27},
		{28,29,30},
		{31,32,33},
		{34,35,36}

	}
	};

	BetType currentBetType;


	void PlayGame()
	{



		User::currentBetAmm = 0;
		game::errorMessage = "Invalid bet option! Try again!";


		if (TrySelectBetType(currentBetType))
		{
			game::currentGameState = game::GameState::Error;
			return;
		}

		if (!User::TrySetABet(game::currentGameMode))
		{
			return;
		}



		switch (currentBetType)
		{
			case Roullete::BetType::Straight:
				User::hasUserWon = TryGuessANumber();
				break;
			case Roullete::BetType::Split:
				break;
			case Roullete::BetType::Corner:
				break;
			case Roullete::BetType::OddOrEven:
				break;
			case Roullete::BetType::Column:
				break;
			case Roullete::BetType::RedOrBlack:
				break;


		}

		game::currentGameState = User::hasUserWon ? game::GameState::Won : game::GameState::Lost;
	}


	bool TryGuessANumber()
	{
		system("cls");
		std::cout << "Select a number between " << roulleteStartingNumber << " and " << roulleteNumberAmm << ": ";
		int userInput = User::GetConstrainedNumericalUserInput(0, 36);
		if (userInput == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessANumber();
		}

		userInput--;

		if (userInput < 0)
		{
			userInput = 0;
		}


		int verticalRoll = game::RandomNumber(0, 11);
		int horizontalRoll = game::RandomNumber(0, 2);

		int resultingRoll = roulleteBoard[verticalRoll][horizontalRoll];



	}

	bool TrySelectBetType(BetType& aValidBetType)
	{
		std::cout << "How do you want to bet?" << std::endl;

		const std::string straightBet = "straight";
		const std::string splitBet = "split";
		const std::string redOrBlackBet = "redorblack";
		const std::string oddOrEvenBet = "oddoreven";
		const std::string columnBet = "column";


		const std::array<std::string, 20> betOptions = {
			straightBet, splitBet, redOrBlackBet, oddOrEvenBet,
			columnBet
		};

		std::string userInput = User::GetUserInput(betOptions);

		if (userInput == User::invalidInput)
		{
			return false;
		}
		else if (userInput == straightBet)
		{
			aValidBetType = BetType::Straight;
		}
		else if (userInput == splitBet)
		{
			aValidBetType = BetType::Split;
		}
		else if (userInput == redOrBlackBet)
		{
			aValidBetType = BetType::RedOrBlack;
		}
		else if (userInput == oddOrEvenBet)
		{
			aValidBetType = BetType::OddOrEven;
		}
		else if (userInput == columnBet)
		{
			aValidBetType = BetType::Column;
		}

		return true;

	}









}