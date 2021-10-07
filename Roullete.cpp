#include "Roullete.h"
#include <Windows.h>

namespace game = RuntimeManagement;

namespace Roulette
{
	const int rouletteStartingNumber = 0;
	const int rouletteNumberAmm = 36;
	const int roulleteRowAmm = 12;
	const int roulleteCollumAmm = 3;

	const std::array<int, 6> rouletteCornerPairs = {
			1,
			4,
			5,
			8,
			9,
			12,
	};


	std::array<std::string, 20> userInstructions = {
		"The rules are as follows!\n",
		"You begin by deciding how you are going to bet into roulette.\n",
		"This decision will determine how roulette is going to be played.\n",
		"Once you have come to a choice, a board is going to appear and we will instruct you what to do next!\n",
	};

	const std::array<std::array < int, 3>, 13> rouletteBoard = { {
		{ 0, 0, 0}, //0 (Not counting)
		{ 1, 2, 3}, //1 -
		{ 4, 5, 6}, //2
		{ 7, 8, 9}, //3
		{10,11,12}, //4 -
		{13,14,15}, //5 -
		{16,17,18}, //6
		{19,20,21}, //7
		{22,23,24}, //8 -
		{25,26,27}, //9 -
		{28,29,30}, //10
		{31,32,33}, //11
		{34,35,36}  //12 -

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

	const std::array<std::array < NumberType, 3>, 13> rouletteBlackOrRedDef = { {
		{NumberType::Red, NumberType::Red, NumberType::Red},
		{NumberType::Red, NumberType::Black, NumberType::Red},
		{NumberType::Black, NumberType::Red, NumberType::Black},
		{NumberType::Red, NumberType::Black, NumberType::Red},
		{NumberType::Black, NumberType::Black,  NumberType::Red},
		{NumberType::Black,  NumberType::Red, NumberType::Black},
		{NumberType::Red, NumberType::Black,  NumberType::Red},
		{NumberType::Red,NumberType::Black,  NumberType::Red},
		{NumberType::Black,  NumberType::Red, NumberType::Black},
		{NumberType::Red, NumberType::Black, NumberType::Red},
		{NumberType::Black,NumberType::Black,  NumberType::Red},
		{NumberType::Black,  NumberType::Red, NumberType::Black},
		{NumberType::Red, NumberType::Black,  NumberType::Red}

   }
	};

	BetType currentBetType;
	NumberType chosenNumberType;

	void ResetBoard()
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
	}
	void PlayGame()
	{
		chosenNumberType = NumberType::None;
		ResetBoard();
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
			case Roulette::BetType::OddOrEven:
			case Roulette::BetType::Straight:
			case Roulette::BetType::RedOrBlack:
			case Roulette::BetType::Column:
				{
					User::hasUserWon = TryGuessANumber();
					break;
				}
			case Roulette::BetType::Corner:
			case Roulette::BetType::Split:
				{
					User::hasUserWon = TryGuessTwoNumbersWithAConstraint();
					break;
				}
		}


		std::cin.clear();
		std::cin.ignore(10000, '\n');
		game::currentGameState = User::hasUserWon ? game::GameState::Won : game::GameState::Lost;
	}



	bool TryGuessTwoNumbersWithAConstraint()
	{
		ResetBoard();
		system("cls");
		DrawBoard();
		std::cout << "Select two numbers that are adjacent to " << (currentBetType == BetType::Split ? "4" : "3") << " different numbers. Select a number between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ".\nFirst Number:";
		int firstNumber = Search(rouletteBoard, User::GetConstrainedNumericalUserInput(0, rouletteNumberAmm));


		if (firstNumber == User::invalidNumericalInput)
		{
			std::cout << game::errorMessage << std::endl;
			system("pause");
			return TryGuessTwoNumbersWithAConstraint();
		}
		std::array<std::array<int, 2>, 12> foundLegalPositions = GetLegalPositions(firstNumber);


		const int cornerSize = 4;
		if (currentBetType == BetType::Corner)
			for (int y = 0; y < foundLegalPositions.size(); y++)
			{
				if (IsPositionOutOfBounds(foundLegalPositions[y]) && y < cornerSize)
				{
					std::cout << game::errorMessage << std::endl;
					system("pause");
					return TryGuessTwoNumbersWithAConstraint();
				}
			}

		SelectElementFromBoard(firstNumber, SelectionType::User);
		for (int y = 0; y < foundLegalPositions.size(); y++)
		{
			if (IsPositionOutOfBounds(foundLegalPositions[y])) continue;
			rouletteSelectionBoard[foundLegalPositions[y][0]][foundLegalPositions[y][1]] = SelectionType::LegalOption;

		}




		system("cls");
		DrawBoard();
		std::cout << "Select two numbers that are adjacent to " << (currentBetType == BetType::Split ? "4" : "3") << " different numbers. Select a number between " << firstNumber << " and " << GetValueFromPosition(foundLegalPositions[3]) << ".\n";
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


	std::array<std::array<int, 2>, 12> GetLegalPositions(int anOriginPoint)
	{
		std::array<int, 2> anOriginPointGridPos = GetPositionOfElement(rouletteBoard, anOriginPoint);
		return GetLegalNumbers(anOriginPointGridPos);
	}

	int GetValidatedNumberThatIsAdjacent(std::array<std::array<int, 2>, 12> someLegalPositions, int aNewNumber)
	{

		if (aNewNumber == User::invalidNumericalInput) return User::invalidNumericalInput;


		std::array<int, 2> aNewNumberGridPos = GetPositionOfElement(rouletteBoard, aNewNumber);

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

	std::array<int, 2> GetPositionOfElement(std::array<std::array<int, 3>, 13> aBoard, int anElementToFindIndex)
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


	std::array < std::array <int, 2>, 12 > GetLegalNumbers(std::array<int, 2> aGridCoordinate)
	{
		std::array< std::array <int, 2>, 12> result = { {
					{User::invalidNumericalInput, User::invalidNumericalInput },
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput },
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput },
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput},
					{User::invalidNumericalInput, User::invalidNumericalInput}
			}
		};
		const int y = aGridCoordinate[0];
		const int x = aGridCoordinate[1];

		switch (currentBetType)
		{
			case Roulette::BetType::Split:
				{

					const int upperYIndex = y + 1;
					const int lowerYIndex = y - 1;

					const int upperXIndex = x + 1;
					const int lowerXIndex = x - 1;

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
				{
					for (int i = 0; i < rouletteCornerPairs.size(); i++)
					{
						const int bottomY = y + 3;
						const int topY = y;

						if (topY == rouletteCornerPairs[i])//If we are on the top side
						{
							if (x == 0) //If we are on the left side of the board
							{
								result[0] = { topY, x };
								result[1] = { topY + 1, x };
								result[2] = { topY, x + 1 };
								result[3] = { topY + 1, x + 1 };
							}
							else if (x == rouletteBoard[topY].size() - 1)//If we are on the right side of the board
							{
								result[0] = { topY, x };
								result[1] = { topY + 1, x };
								result[2] = { topY, x - 1 };
								result[3] = { topY + 1, x - 1 };
							}
							break;

						}
						else if (bottomY == rouletteCornerPairs[i])//If we are on the bottom side
						{
							if (x == 0) //If we are on the left side of the board
							{
								result[0] = { topY, x };
								result[1] = { topY - 1, x };
								result[2] = { topY, x + 1 };
								result[3] = { topY - 1, x + 1 };
							}
							else if (x == rouletteBoard[bottomY].size() - 1)//If we are on the right side of the board
							{
								result[0] = { topY, x };
								result[1] = { topY - 1, x };
								result[2] = { topY, x - 1 };
								result[3] = { topY - 1, x - 1 };
							}
							break;
						}


					}
					break;
				}

			case Roulette::BetType::Column:
				{
					for (int column = 1; column < rouletteBoard.size(); column++)
					{
						result[column - 1] = { column, x };
					}
					break;
				}


		}

		return result;

	}

	void DrawBoard()
	{
		const int singleDigidElements = 4;
		const std::string userSelectionGraphic = "#";
		const std::string gameSelectionGraphic = "X";


		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

		const int whiteColor = 15;
		const int pinkColor = 13;
		const int cyanColor = 11;
		const int greyColor = 8;
		const int redColor = 12;
		const int greenColor = 10;

		SetConsoleTextAttribute(h, whiteColor);
		switch (rouletteSelectionBoard[0][0])
		{
			case SelectionType::User:
				{
					SetConsoleTextAttribute(h, pinkColor);
					std::cout << std::string("   [" + userSelectionGraphic + "]");
					break;
				}
			case SelectionType::Game:
				{
					SetConsoleTextAttribute(h, cyanColor);
					std::cout << std::string("   [" + gameSelectionGraphic + "]");
					break;
				}
			case SelectionType::LegalOption:
				{
					SetConsoleTextAttribute(h, greenColor);
					std::cout << std::string("   []");
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

				switch (rouletteBlackOrRedDef[y][x])
				{
					case NumberType::Black:
						{
							SetConsoleTextAttribute(h, greyColor);
							break;
						}

					case NumberType::Red:
						{
							SetConsoleTextAttribute(h, redColor);
							break;
						}

				}


				if (x == 0)
				{
					std::cout << (y < singleDigidElements ? " [" : "[");
				}
				switch (rouletteSelectionBoard[y][x])
				{
					case SelectionType::User:
						{
							SetConsoleTextAttribute(h, pinkColor);
							std::cout << userSelectionGraphic;
							break;
						}
					case SelectionType::Game:
						{
							SetConsoleTextAttribute(h, cyanColor);
							std::cout << (y < singleDigidElements ? gameSelectionGraphic : " " + gameSelectionGraphic);
							break;
						}
					case SelectionType::None:
					case SelectionType::LegalOption:
						{
							if (rouletteSelectionBoard[y][x] == SelectionType::LegalOption)
								SetConsoleTextAttribute(h, greenColor);
							std::cout << std::to_string(rouletteBoard[y][x]);
							break;
						}
				}

				if (x == rouletteBoard[y].size() - 1)
				{

					std::cout << "]";
				}
				else
				{

					
					std::cout << "|";




				}
			}
			SetConsoleTextAttribute(h, whiteColor);
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


		std::array<int, 2> numberPos = GetPositionOfElement(rouletteBoard, aNumberToSelect);
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
		ResetBoard();
		system("cls");

		switch (currentBetType)
		{
			case BetType::Column:
			case Roulette::BetType::Straight:
				{
					DrawBoard();
					int resultingRoll = GetRandomNumberFromRoulette();
					SelectElementFromBoard(resultingRoll, SelectionType::Game);

					std::cout << "Select a number between " << rouletteStartingNumber << " and " << rouletteNumberAmm << ": ";
					int userInput = User::GetConstrainedNumericalUserInput(0, 36);
					if (userInput == User::invalidNumericalInput)
					{
						std::cout << game::errorMessage << std::endl;
						system("pause");
						return TryGuessANumber();
					}
					SelectElementFromBoard(userInput, SelectionType::User);

					if (currentBetType == BetType::Straight)
					{
						std::cout << "Number rolled: " << resultingRoll << "\nUser guess: " << userInput << std::endl;
						system("pause");


						return userInput == resultingRoll;
					}
					else
					{
						std::cout << "Number rolled: " << resultingRoll << std::endl;
						std::array<std::array<int, 2>, 12> legalOptions = GetLegalPositions(resultingRoll);

						const int selectedColumn = legalOptions[0][1];


						for (int i = 0; i < legalOptions.size(); i++)
						{
							if (IsPositionOutOfBounds(legalOptions[i])) continue;

							int value = GetValueFromPosition(legalOptions[i]);
							SelectElementFromBoard(value, value == userInput ? SelectionType::Game : SelectionType::LegalOption);
							if (value == userInput)
							{
								DrawBoard();
								return true;
							}

						}
						DrawBoard();
						std::cout << "Guessed wrong! The" << (selectedColumn == 0 ? " left " : selectedColumn == rouletteBoard[0].size() - 1 ? " right " : " middle ") << "column was chosen!" << std::endl;
						return false;
					}
					break;

				}


			case Roulette::BetType::OddOrEven:
			case Roulette::BetType::RedOrBlack:
				{
					DrawBoard();
					std::cout << "Make a guess on whether or not the resulting number is" << (currentBetType == BetType::OddOrEven ? " even or odd: " : " a red or a black number: ");


					int resultingRoll = GetRandomNumberFromRoulette();
					SelectElementFromBoard(resultingRoll, SelectionType::Game);




					switch (currentBetType)
					{

						case Roulette::BetType::OddOrEven:
							{


								const std::string oddOption = "odd", evenOption = "even";

								std::array < std::string, 20> oddOrEvenOptions = { oddOption, evenOption };
								std::string userInput = User::GetUserInput(oddOrEvenOptions);


								if (userInput == oddOption)
								{
									DrawBoard();
									std::cout << (resultingRoll % 2 != 0 ? "The roll was guessed corretly! The number is odd! Result: " : "The roll was guessed incorrectly! The number is even! Result: ") << resultingRoll << std::endl;
									return resultingRoll % 2 != 0;
								}
								else if (userInput == evenOption)
								{
									DrawBoard();
									std::cout << (resultingRoll % 2 == 0 ? "The roll was guessed corretly! The number is even! Result:" : "The roll was guessed incorrectly! The number is odd! Result: ") << resultingRoll << std::endl;
									return resultingRoll % 2 == 0;
								}
								else if (userInput == User::invalidInput)
								{
									return TryGuessANumber();
								}
								break;
							}


						case Roulette::BetType::RedOrBlack:
							{

								const std::string blackOption = "black", redOption = "red";

								std::array < std::string, 20> blackOrRedOptions = { blackOption, redOption };
								std::string userInput = User::GetUserInput(blackOrRedOptions);

								if (userInput == User::invalidInput)
								{
									return TryGuessANumber();
								}

								chosenNumberType = userInput == blackOption ? NumberType::Black : userInput == redOption ? NumberType::Red : NumberType::None;


								return chosenNumberType == GetNumberType(GetPositionOfElement(rouletteBoard, resultingRoll));

								break;
							}


					}


					return false;
				}






		}


		return false;




	}


	NumberType GetNumberType(std::array<int, 2> aGridCoordinate)
	{
		return rouletteBlackOrRedDef[aGridCoordinate[0]][aGridCoordinate[1]];
	}

	bool TrySelectBetType(BetType& aValidBetType)
	{
		std::cout << "How do you want to bet? <[Straight|Split|Corner|RedOrBlack|OddOrEven|Column]>: " << std::endl;

		const std::string straightBet = "straight";
		const std::string splitBet = "split";
		const std::string cornerBet = "corner";
		const std::string redOrBlackBet = "redorblack";
		const std::string oddOrEvenBet = "oddoreven";
		const std::string columnBet = "column";


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