#include "GuessADoor.h"

namespace game = RuntimeManagement;

namespace GuessADoor
{
	const int doorDrawLines = 6;
	const int doorAmm = 5;
	const int minDiceRoll = 1, maxDiceRoll = 5;
	const int maxAttemptsAtGuessing = 3;
	std::array<std::string, 20> userInstructions = {
	"The rules are simple!\n",
	"We will offer you " + std::to_string(maxDiceRoll) + " doors to choose from.\n",
	"You have " + std::to_string(maxAttemptsAtGuessing) + " attempts at guessing which door is golden before loosing!\n"
	};

	std::array<std::string, doorAmm> currentDoors;


	void PlayGame()
	{
		game::currentGameState = game::GameState::Lost;
		User::hasUserWon = false;
		game::errorMessage = "Invalid number. Try again!";
		User::currentBetAmm = 0;

		if (!User::TrySetABet(game::currentGameMode))
		{
			return;
		}


		int chosenDoor = GenerateResults();
		int currentUserAttempts = maxAttemptsAtGuessing;

		std::array<bool, doorAmm> currentActiveDoors;

		for (int i = 0; i < currentActiveDoors.size(); i++)
		{
			currentActiveDoors[i] = true;
		}

		while (!User::hasUserWon)
		{
			if (currentUserAttempts == 0)
			{
				break;
			}

			system("cls");
			std::cout << "You have " << currentUserAttempts << " attempts left!" << std::endl;
			int doorCount = 0;



			for (int i = 0; i < doorDrawLines; i++)
			{
				for (int x = 0; x < currentDoors.size(); x++)
				{
					if (currentActiveDoors[x])
					{
						currentDoors[x] = DrawDoorSymbols(x, i, " ", " ");
						std::cout << currentDoors[x];
					}

				}
				std::cout << std::endl;

			}


			std::cout << "Guess which of these doors is golden!" << std::endl;
			std::cout << "Guess (with a number): ";
			int input = User::GetConstrainedNumericalUserInput(1, doorAmm);

			if (input == User::invalidNumericalInput)
			{
				game::currentGameState = game::GameState::Error;
				break;
			}

			input--;
			if (input == chosenDoor)
			{
				system("cls");
				User::hasUserWon = true;
				std::cout << "You found the golden door!" << std::endl;
				game::currentGameState = game::GameState::Won;
				DrawDoor(input, false);


			}
			else if (currentUserAttempts > 0)
			{

				currentActiveDoors[input] = false;
				currentUserAttempts--;
			}
			else
			{
				break;
			}
		}


		//Roll a dice from 1 to 5 to select desired door
		//Have the player choose a door 3 times before loosing.





	}

	void DrawDoor(int aDoorIndex, bool aEnterSkip = false)
	{
		for (int i = 0; i < doorDrawLines; i++)
		{
			currentDoors[aDoorIndex] = DrawDoorSymbols(aDoorIndex, i, "        ", "        ");
			std::cout << currentDoors[aDoorIndex];
			if (!aEnterSkip)
				std::cout << std::endl;

		}
	}


	int GenerateResults()
	{
		return game::RandomNumber(minDiceRoll, maxDiceRoll);
	}

	std::string DrawDoorSymbols(int aDoorIndex, int aCurrentDrawLine, std::string aLeftSideSpacing = "", std::string aRightSideSpacing = "")
	{
		switch (aCurrentDrawLine)
		{
			case 0:
				return aLeftSideSpacing + "|||||||||" + aRightSideSpacing;
			case 2:
				return aLeftSideSpacing + "|---" + std::to_string(aDoorIndex + 1) + "---|" + aRightSideSpacing;
			case 3:
				return aLeftSideSpacing + "|------o|" + aRightSideSpacing;
			case doorDrawLines - 1:
			default:
				return aLeftSideSpacing + "|-------|" + aRightSideSpacing;
		}

	}




}