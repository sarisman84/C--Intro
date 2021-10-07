#include "Player.h"

namespace game = RuntimeManagement;

namespace User
{
	int currentCapitalAmm = 0;
	int currentBetAmm = 0;
	std::string introductionMessage = "";
	bool hasUserWon = false;


	int currentUserProfitInRollADice;
	int currentUserProfitInOddOrEven;
	int currentUserProfitInRollADiceLite;
	int currentUserProfitInGuessADoor;
	int currentUserProfitInRoullete;
	int currentUserProfitInDebug;

	const std::string invalidInput = "NaN";
	const int invalidNumericalInput = -200;
	const int reactionThresholdOnCapitalChange = 5000;


	bool IsBetAmmValid(int aBetAmm)
	{
		return aBetAmm > 1 && aBetAmm <= currentCapitalAmm;
	}

	bool HasCapital()
	{
		return currentCapitalAmm > 0;
	}


	bool TrySetABet(game::GameMode aCurrentGameMode)
	{
		system("CLS");
		std::cout << "Current amount of cash: " << currentCapitalAmm << "\n";

		std::string multiplierOutput = "[x" + std::to_string(game::CurrentGameModeEarningsMultiplier()) + "]";



		std::cout << "Bet an amount of cash (" << multiplierOutput << "cash amount upon winning!):";
		int userAssignedAmm;
		std::cin >> userAssignedAmm;
		if (User::IsBetAmmValid(userAssignedAmm) && !std::cin.fail())
		{
			User::currentBetAmm = userAssignedAmm;
			User::currentCapitalAmm -= userAssignedAmm;

			std::string output = "Assigned bet accepted! -> ";
			if (User::currentCapitalAmm <= 0)
			{
				output = "Going all in i see! Ill allow it! -> ";
			}

			std::cout << output << User::currentBetAmm << " (" << multiplierOutput << "cash amount upon winning!)\n";
			system("pause");
			return true;
		}
		else
		{
			game::errorMessage = "Invalid bet amount! Try again!";
			std::cout << game::errorMessage << std::endl;
			return TrySetABet(aCurrentGameMode);
		}
		return false;
	}

	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName)
	{
		std::cout << "You are about to play " << aGameModeName << ". Continue? [Yes/No] ";
		const std::string answerYes = "yes", answerNo = "no";
		const int contextPhrasesToSelectSize = 2;
		std::string contextPhrasesToSelect[] = { answerYes, answerNo };
		std::string userInput = GetUserInput(contextPhrasesToSelect, contextPhrasesToSelectSize);

		if (userInput == invalidInput)
		{
			game::currentGameState = game::GameState::Error;
			return;
		}
		else if (userInput == answerNo)
		{
			game::currentGameState = game::GameState::Menu;
			game::currentGameMode = game::GameMode::None;
			system("CLS");
			return;
		}
	}






	void DisplayStringArrayToConsole(std::array<std::string, 20> someInstructions)
	{
		std::string displayMessage;
		system("CLS");
		for (auto beg = someInstructions.begin(); beg != someInstructions.end(); ++beg)
		{
			if (*beg == "") continue;
			system("CLS");
			displayMessage += *beg;


			std::cout << displayMessage << std::endl;


			system("pause");
		}

		system("CLS");
	}

	void EarnCapital()
	{
		User::currentBetAmm = User::currentBetAmm * game::CurrentGameModeEarningsMultiplier();

		User::currentCapitalAmm += User::currentBetAmm;

		switch (game::currentGameMode)
		{
			case game::GameMode::RollADice:
				{
					currentUserProfitInRollADice += currentBetAmm;
					break;
				}

			case game::GameMode::OddOrEven:
				{
					currentUserProfitInOddOrEven += currentBetAmm;
					break;
				}

			case game::GameMode::RollADiceLite:
				{
					currentUserProfitInRollADiceLite += currentBetAmm;
					break;
				}
			case game::GameMode::GuessADoor:
				{
					currentUserProfitInGuessADoor += currentBetAmm;

					break;
				}
			case game::GameMode::Debug:
				{
					currentUserProfitInDebug += currentBetAmm;
					break;
				}
			case game::GameMode::Roullete:
				{
					currentUserProfitInRoullete += currentBetAmm;
					break;
				}


		}

		std::cout <<
			"Earned " << User::currentBetAmm << " cash. You have " << User::currentCapitalAmm << " cash now!\n\n";

		if (HasEarningsReachedThreshold(reactionThresholdOnCapitalChange, game::currentGameMode))
		{
			std::cout << "Poggers, you managed to earn over 500 cash! Literal god. :D" << std::endl;
		}
	}

	void PayCapital()
	{
		switch (game::currentGameMode)
		{
			case game::GameMode::RollADice:
				{

					currentUserProfitInRollADice -= currentBetAmm;
					if (currentUserProfitInRollADice < 0)
					{
						currentUserProfitInRollADice = 0;
					}

					break;
				}

			case game::GameMode::OddOrEven:
				{
					currentUserProfitInOddOrEven -= currentBetAmm;
					if (currentUserProfitInOddOrEven < 0)
					{
						currentUserProfitInOddOrEven = 0;
					}

					break;
				}

			case game::GameMode::RollADiceLite:
				{

					currentUserProfitInRollADiceLite -= currentBetAmm;
					if (currentUserProfitInRollADiceLite < 0)
					{
						currentUserProfitInRollADiceLite = 0;
					}

					break;
				}

			case game::GameMode::GuessADoor:
				{
					currentUserProfitInGuessADoor -= currentBetAmm;
					if (currentUserProfitInGuessADoor < 0)
					{
						currentUserProfitInGuessADoor = 0;
					}

					break;
				}

			case game::GameMode::Debug:
				{
					currentUserProfitInDebug -= currentBetAmm;
					if (currentUserProfitInDebug < 0)
					{
						currentUserProfitInDebug = 0;
					}
					break;
				}
			case game::GameMode::Roullete:
				{
					currentUserProfitInRoullete -= currentBetAmm;
					if (currentUserProfitInRoullete < 0)
					{
						currentUserProfitInRoullete = 0;
					}
					break;
				}


		}

		std::cout << std::endl << "Lost " << User::currentBetAmm << " cash. " << User::currentCapitalAmm << " remain!\n\n";

		if (HasEarningsReachedThreshold(reactionThresholdOnCapitalChange, game::currentGameMode))
		{
			std::cout << "Massive sadge, loosing over 500 cash.. You'll recoupe. :)" << std::endl << std::endl;
		}
	}

	int GetConstrainedNumericalUserInput(int aMinInputValue, int aMaxInputValue)
	{
		int userInput;
		std::cin >> userInput;
		if (userInput < aMinInputValue || userInput > aMaxInputValue || std::cin.fail())
		{
			userInput = invalidNumericalInput;
			std::cin.clear(); //Clears the stream buffer.
			std::cin.ignore(10000, '\n'); //Clears the input field.
		}

		std::cin.ignore(10000, '\n');
		return userInput;
	}


	//Thank Linus for telling me the altenative way of using a for loop.
	void ToLower(std::string& someValue)
	{
		//The below loop was written based of this article on how to lower case a character in C++
		//Source: https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/

		for (auto& letter : someValue)
		{
			letter = std::tolower(letter);
		}

	}

	void RemoveSpaces(std::string& someValue)
	{
		std::string newString = "";
		for (auto& letter : someValue)
		{
			if (static_cast<int>(letter) != 32)
			{
				newString += letter;
			}
			
		}
		someValue = newString;

		
	}

	std::string GetUserInput(std::string someAcceptablePhrases[], int anArraySize = 1)
	{
		std::string userInput;
		std::getline(std::cin, userInput);
		RuntimeManagement::DebugPrint(userInput);
		ToLower(userInput);
		RemoveSpaces(userInput);

		for (int i = 0; i < anArraySize; i++)
		{
			if (userInput == someAcceptablePhrases[i])
				return userInput;
		}


		userInput = invalidInput;
		return userInput;
	}

	std::string GetUserInput(std::array<std::string, 20> someAcceptablePhrases)
	{
		std::string userInput;
		std::getline(std::cin, userInput);
		ToLower(userInput);
		RemoveSpaces(userInput);

		for (int i = 0; i < someAcceptablePhrases.size(); i++)
		{
			if (someAcceptablePhrases[i] == "") continue;

			if (userInput == someAcceptablePhrases[i])
				return userInput;
		}


		userInput = invalidInput;
		return userInput;
	}



	int GetNumericalUserInput(int someAllowedValues[])
	{
		int userInput;
		std::cin >> userInput;



		//Based of this article on how to get the size of an array: 
		//https://www.educative.io/edpresso/how-to-find-the-length-of-an-array-in-cpp

		int arraySize = *(&someAllowedValues + 1) - someAllowedValues;
		for (int i = 0; i < arraySize; i++)
		{
			if (someAllowedValues[i] == userInput && !std::cin.fail())
			{
				return userInput;
			}
		}

		std::cin.clear();
		std::cin.ignore(1000);
		return invalidNumericalInput;
	}



	bool HasEarningsReachedThreshold(int someLimit, game::GameMode aGameMode)
	{
		switch (aGameMode)
		{
			case game::GameMode::RollADice:
				return currentUserProfitInRollADice > someLimit;
			case game::GameMode::OddOrEven:
				return currentUserProfitInOddOrEven > someLimit;
			case game::GameMode::RollADiceLite:
				return currentUserProfitInRollADiceLite > someLimit;
			case game::GameMode::GuessADoor:
				return currentUserProfitInGuessADoor > someLimit;
			case game::GameMode::Debug:
				return currentUserProfitInDebug > someLimit;
			case game::GameMode::Roullete:
				return currentUserProfitInDebug > someLimit;
			default:
				return false;

		}
	}
}