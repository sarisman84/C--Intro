#include "Roullete.h"


namespace game = RuntimeManagement;

namespace Roulette
{
	const int rouletteStartingNumber = 0;
	const int rouletteNumberAmm = 36;
	const int roulleteRowAmm = 12;
	const int roulleteCollumAmm = 3;


	std::array<std::string, 20> userInstructions = {
		"The rules are as follows!\n",
		"You begin by deciding how you are going to bet into roulette.\n",
		"This decision will determine how roulette is going to be played.\n",
		"Once you have come to a choice, a board is going to appear and we will instruct you what to do next!\n",
	};

	const std::array<std::array < int, 3>, 13> rouletteBoard = { {
		{ 0, 0, 0},
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

	std::array<std::array < SelectionType, 3>, 13> rouletteSelectionBoard = { {
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None}

   }
	};

	BetType currentBetType;
	NumberType chosenNumberType;


	void PlayGame()
	{
		rouletteSelectionBoard = { {
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None},
		{SelectionType::None, SelectionType::None, SelectionType::None}

   }
		};
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
				User::hasUserWon = TryGuessTwoNumbersWithAConstraint();
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


		std::cin.ignore(10000, '\n');
		game::currentGameState = User::hasUserWon ? game::GameState::Won : game::GameState::Lost;
	}

	bool TryGuessACorner()
	{
		system("cls");
		std::cout << "Select one of four numbers that are adjacent to each other between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ".\nFirst Number:";
		return true;
	}

	bool TryGuessTwoNumbersWithAConstraint()
	{

		system("cls");
		DrawBoard();
		std::cout << "Select two adjacent numbers between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ".\nFirst Number:";
		int firstNumber = Search(rouletteBoard, User::GetConstrainedNumericalUserInput(0, rouletteNumberAmm));


		if (firstNumber == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessTwoNumbersWithAConstraint();
		}

		SelectElementFromBoard(firstNumber, SelectionType::User);
		std::array<std::array<int, 2>, 4> foundLegalPositions = GetLegalPositions(firstNumber);

		for (int y = 0; y < foundLegalPositions.size(); y++)
		{
			if (IsPositionOutOfBounds(foundLegalPositions[y])) continue;
			rouletteSelectionBoard[foundLegalPositions[y][0]][foundLegalPositions[y][1]] = SelectionType::LegalOption;

		}


		system("cls");
		DrawBoard();
		std::cout << "Select two adjacent numbers between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ".\n";
		std::cout << "Second Number:";



		int secondNumber = GetValidatedNumberThatIsAdjacent(foundLegalPositions, Search(rouletteBoard, User::GetConstrainedNumericalUserInput(rouletteStartingNumber, rouletteNumberAmm)));



		if (secondNumber == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessTwoNumbersWithAConstraint();
		}
		SelectElementFromBoard(secondNumber, SelectionType::User);
		int randomNumber = GetRandomNumberFromRoulette();

		SelectElementFromBoard(randomNumber, SelectionType::Game);
		system("cls");

		DrawBoard();
		std::cout << "RNGJesus dictated that " << randomNumber << " will be selected!";

		return randomNumber == firstNumber || randomNumber == secondNumber;

	}

	int GetValueFromPosition(std::array<int, 2> aPosition)
	{
		if (aPosition[0] == User::invalidNumericalInput || aPosition[1] == User::invalidNumericalInput) return User::invalidNumericalInput;

		return rouletteBoard[aPosition[0]][aPosition[1]];
	}


	std::array<std::array<int, 2>, 4> GetLegalPositions(int anOriginPoint)
	{
		std::array<int, 2> anOriginPointGridPos = GetIndex(rouletteBoard, anOriginPoint);
		return GetLegalNumbers(anOriginPointGridPos);
	}

	int GetValidatedNumberThatIsAdjacent(std::array<std::array<int, 2>, 4> someLegalPositions, int aNewNumber)
	{

		if (aNewNumber == User::invalidNumericalInput) return User::invalidNumericalInput;


		std::array<int, 2> aNewNumberGridPos = GetIndex(rouletteBoard, aNewNumber);

		for (int legalIndex = 0; legalIndex < someLegalPositions.size(); legalIndex++)
		{
			if (someLegalPositions[legalIndex][0] == aNewNumberGridPos[0] &&
				someLegalPositions[legalIndex][1] == aNewNumberGridPos[1])
			{
				return aNewNumber;
			}
		}

		return User::invalidNumericalInput;

	}

	int Search(std::array<std::array<int, 3>, 13> aBoard, int anElementToFind)
	{
		for (int y = 0; y < aBoard.size(); y++)
		{
			for (int x = 0; x < aBoard[y].size(); x++)
			{
				if (aBoard[y][x] == anElementToFind)
				{
					return aBoard[y][x];
				}
			}
		}
		return User::invalidNumericalInput;
	}

	std::array<int, 2> GetIndex(std::array<std::array<int, 3>, 13> aBoard, int anElementToFindIndex)
	{
		std::array<int, 2> result = { User::invalidNumericalInput, User::invalidNumericalInput };
		for (int y = 0; y < aBoard.size(); y++)
		{
			for (int x = 0; x < aBoard[y].size(); x++)
			{
				if (aBoard[y][x] == anElementToFindIndex)
				{
					result[0] = y;
					result[1] = x;
					return result;
				}
			}
		}
		return result;
	}


	std::array < std::array <int, 2>, 4 > GetLegalNumbers(std::array<int, 2> aGridCoordinate)
	{
		std::array< std::array <int, 2>, 4> result = { {
					{User::invalidNumericalInput, User::invalidNumericalInput },
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput} }
		};
		const int y = aGridCoordinate[0];
		const int x = aGridCoordinate[1];

		switch (currentBetType)
		{
			case Roulette::BetType::Split:
				{


					int upperYIndex = y + 1;
					int lowerYIndex = y - 1;

					int upperXIndex = x + 1;
					int lowerXIndex = x - 1;

					if (upperYIndex < rouletteBoard.size())
					{
						result[0] = { upperYIndex, x };
					}

					if (lowerYIndex >= 0)
					{
						result[1] = { lowerYIndex, x };
					}

					if (upperXIndex < rouletteBoard[y].size())
					{
						result[2] = { y, upperXIndex };

					}
					if (lowerXIndex >= 0)
					{
						result[3] = { y, lowerXIndex };
					}

					break;
				}

			case Roulette::BetType::Corner:
				break;
			case Roulette::BetType::OddOrEven:
				{
					
						switch (chosenNumberType)
						{
							case NumberType::Odd:
								{
									if (x % 2 != 0 && y % 2 != 0)
										result[0] = { y, x };
									else if (x % 2 != 0)
										result[0] = { -1, x };
									else if (y % 2 != 0)
										result[0] = { y, -1 };
									break;
								}
							case NumberType::Even:
								{
									if (x % 2 == 0 && y % 2 == 0)
										result[0] = { y, x };
									else if (x % 2 == 0)
										result[0] = { -1, x };
									else if (y % 2 == 0)
										result[0] = { y, -1 };
									break;
								}
						}
					

					break;
				}

			case Roulette::BetType::Column:
				break;
			case Roulette::BetType::RedOrBlack:
				break;
		}

		return result;

	}

	void DrawBoard()
	{
		const int singleDigidElements = 4;
		const std::string userSelectionGraphic = "#";
		const std::string gameSelectionGraphic = "X";

		const std::string legalOptionSelectionGraphicL = "<";
		const std::string legalOptionSelectionGraphicR = ">";
		const std::string legalOptionSelectionGraphicMiddle = "I";

		switch (rouletteSelectionBoard[0][0])
		{
			case SelectionType::User:
				{
					std::cout << std::string("   [" + userSelectionGraphic + "]");
					break;
				}
			case SelectionType::Game:
				{
					std::cout << std::string("   [" + gameSelectionGraphic + "]");
					break;
				}
			case SelectionType::LegalOption:
				{
					std::cout << std::string("   " + legalOptionSelectionGraphicL + gameSelectionGraphic + legalOptionSelectionGraphicR);
					break;
				}
			case SelectionType::None:
				{
					std::cout << "   [0]";
					break;
				}
		}
		std::cout << std::endl;


		for (int y = 0; y < rouletteBoard.size(); y++)
		{
			if (y == 0) continue;
			for (int x = 0; x < rouletteBoard[y].size(); x++)
			{

				if (x == 0)
				{
					std::cout << (rouletteSelectionBoard[y][x] == SelectionType::LegalOption ? (y < singleDigidElements ? " " + legalOptionSelectionGraphicL : legalOptionSelectionGraphicL) : (y < singleDigidElements ? " [" : "["));
				}
				switch (rouletteSelectionBoard[y][x])
				{
					case SelectionType::User:
						{
							std::cout << userSelectionGraphic;
							break;
						}
					case SelectionType::Game:
						{
							std::cout << (y < singleDigidElements ? gameSelectionGraphic : " " + gameSelectionGraphic);
							break;
						}
					case SelectionType::None:
					case SelectionType::LegalOption:
						{
							std::cout << std::to_string(rouletteBoard[y][x]);
							break;
						}
				}

				if (x == rouletteBoard[y].size() - 1)
				{

					std::cout << (rouletteSelectionBoard[y][x] == SelectionType::LegalOption ? legalOptionSelectionGraphicR : "]");
				}
				else
				{

					const int xNext = x + 1;
					std::cout << (rouletteSelectionBoard[y][x] == SelectionType::LegalOption || (x == 0 && rouletteSelectionBoard[y][xNext] == SelectionType::LegalOption) ? legalOptionSelectionGraphicMiddle : "|");




				}
			}
			std::cout << std::endl;
		}
	}

	void SelectElementFromBoard(int aNumberToSelect, SelectionType aSelectionOwner)
	{
		if (aNumberToSelect == User::invalidNumericalInput)
		{
			return;
		}

		if (aNumberToSelect == 0)
		{
			rouletteSelectionBoard[0][0] = aSelectionOwner;
		}


		std::array<int, 2> numberPos = GetIndex(rouletteBoard, aNumberToSelect);
		const int y = numberPos[0];
		const int x = numberPos[1];
		rouletteSelectionBoard[y][x] = aSelectionOwner;
	}


	bool IsPositionOutOfBounds(std::array<int, 2> aGridPosition)
	{
		const int y = 0, x = 1;
		return aGridPosition[y] == User::invalidNumericalInput || aGridPosition[x] == User::invalidNumericalInput;
	}

	int GetRandomNumberFromRoulette()
	{
		int verticalRoll = game::RandomNumber(0, 11);
		int horizontalRoll = game::RandomNumber(0, 2);

		return rouletteBoard[verticalRoll][horizontalRoll];
	}


	bool TryGuessANumber()
	{
		system("cls");
		DrawBoard();
		std::cout << "Select a number between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ": ";
		int userInput = User::GetConstrainedNumericalUserInput(0, 36);
		if (userInput == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessANumber();
		}
		SelectElementFromBoard(userInput, SelectionType::User);


		int resultingRoll = GetRandomNumberFromRoulette();
		SelectElementFromBoard(resultingRoll, SelectionType::Game);
		std::cout << "Number rolled: " << resultingRoll << "\nUser guess: " << userInput << std::endl;
		system("pause");


		return userInput == resultingRoll;






	}

	bool TrySelectBetType(BetType& aValidBetType)
	{
		std::cout << "How do you want to bet? <[Straight|Split|Corner|RedOrBlack|OddOrEven|Column]>: " << std::endl;

		const std::string straightBet = "straight";
		const std::string splitBet = "split";
		const std::string columnBet = "corner";
		const std::string redOrBlackBet = "redorblack";
		const std::string oddOrEvenBet = "oddoreven";
		const std::string cornerBet = "column";


		const std::array<std::string, 20> betOptions = {
			straightBet, splitBet, redOrBlackBet, oddOrEvenBet,
			columnBet, cornerBet
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
		else if (userInput == cornerBet)
		{
			aValidBetType = BetType::Corner;
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