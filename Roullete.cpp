#include "Roullete.h"


namespace game = RuntimeManagement;

namespace Roulette
{
	const int rouletteStartingNumber = 0;
	const int rouletteNumberAmm = 36;
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

		system("cls");

		User::currentBetAmm = 0;
		game::errorMessage = "Invalid bet option! Try again!";


		if (!TrySelectBetType(currentBetType))
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
			case Roulette::BetType::Straight:
				User::hasUserWon = TryGuessANumber();
				break;
			case Roulette::BetType::Split:
				User::hasUserWon = TryGuessASplit();
				break;
			case Roulette::BetType::Corner:
				break;
			case Roulette::BetType::OddOrEven:
				break;
			case Roulette::BetType::Column:
				break;
			case Roulette::BetType::RedOrBlack:
				break;


		}

		game::currentGameState = User::hasUserWon ? game::GameState::Won : game::GameState::Lost;
	}

	bool TryGuessASplit()
	{
		system("cls");
		std::cout << "Select two adjacent numbers between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ".\nFirst Number:";
		int firstNumber = User::GetConstrainedNumericalUserInput(0, rouletteNumberAmm);

		if (firstNumber == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessASplit();
		}
		std::cout << "Second Number:";
		int secondNumber = GetValidatedNumberThatIsAdjacent(firstNumber, User::GetConstrainedNumericalUserInput(0, rouletteNumberAmm));
	
	}

	int GetValidatedNumberThatIsAdjacent(int anOriginPoint, int aNewNumber)
	{
		
		if (aNewNumber == User::invalidNumericalInput) return User::invalidNumericalInput;





	}


	int Find(std::array<std::array<int, 3>, 12> aBoard, int aNumberToCompare, int &aFoundColumnIndex, int &aFoundRowIndex)
	{
		for (int i = 0; i < aBoard.size(); i++)
		{
			for (int x = 0; x < aBoard[i].size(); x++)
			{
				if (aBoard[i][x] == aNumberToCompare)
				{
					aFoundColumnIndex = i;
					aFoundRowIndex = x;
					return aBoard[i][x];
				}
			}
		}
	}


	bool TryGuessANumber()
	{
		system("cls");
		std::cout << "Select a number between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ": ";
		int userInput = User::GetConstrainedNumericalUserInput(0, 36);
		if (userInput == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessANumber();
		}

		int verticalRoll = game::RandomNumber(0, 11);
		int horizontalRoll = game::RandomNumber(0, 2);

		int resultingRoll = roulleteBoard[verticalRoll][horizontalRoll];

		std::cout << "Number rolled: " << resultingRoll << "\nUser guess: " << userInput << std::endl;
		system("pause");


		return userInput == resultingRoll;






	}

	bool TrySelectBetType(BetType& aValidBetType)
	{
		std::cout << "How do you want to bet?[Straight|Split|RedOrBlack|OddOrEven|Column]: " << std::endl;

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

	int GetBetMultiplier()
	{
		switch (currentBetType)
		{
			case Roulette::BetType::Straight:
				return 10;
			case Roulette::BetType::Split:
				return 3;
			case Roulette::BetType::Corner:
				return 3;
			case Roulette::BetType::OddOrEven:
				return 2;
			case Roulette::BetType::Column:
				return 3;
			case Roulette::BetType::RedOrBlack:
				return 2;
			default:
				return 1;

		}
	}









}