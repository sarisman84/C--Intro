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


	bool TrySetABet(game::GameMode aCurrentGameMode)
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
			User::currentCapitalAmm -= userAssignedAmm;
			std::string output = "Assigned bet accepted! -> ";
			if (currentCapitalAmm == 0)
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
			game::currentGameState = game::GameState::Error;
			return false;
		}
		return false;
	}

	void ConfirmInContinuingPlayingCurrentMode(std::string aGameModeName)
	{
		std::cout << "You are about to play " << aGameModeName << ". Continue? [Yes/No] ";
		std::string contextPhrasesToSelect[] = { "yes", "no" };
		std::string userInput = GetUserInput(contextPhrasesToSelect, 4);

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



	void DisplayStringArrayToConsole(int anArraySize, std::string someInstructions[])
	{
		system("CLS");
		for (int x = 0; x < anArraySize; x++)
		{
			system("CLS");
			for (int i = 0; i <= x; i++)
			{
				std::cout << someInstructions[i] << std::endl;

			}
			system("pause");
		}

		system("CLS");
	}

	void EarnCapital(game::GameMode aCurrentGameMode)
	{
		switch (aCurrentGameMode)
		{

			case RuntimeManagement::GameMode::RollADice:
				{
					User::currentCapitalAmm += User::currentBetAmm * 2;
					std::cout <<
						"Earned " << User::currentBetAmm * 2 << " cash. " << User::currentCapitalAmm << " remain!\n\n";
					break;
				}

			case RuntimeManagement::GameMode::OddOrEven:
				{
					User::currentCapitalAmm += User::currentBetAmm * 3;
					std::cout <<
						"Earned " << User::currentBetAmm * 3 << " cash. " << User::currentCapitalAmm << " remain!\n\n";
					break;
				}


		}


		
	}

	void PayCapital()
	{
		std::cout << "Lost " << User::currentBetAmm << " cash. " << User::currentCapitalAmm << " remain!\n\n";
	}

	int GetConstrainedNumericalUserInput(int aMinInputValue, int aMaxInputValue)
	{
		int userInput;
		std::cin >> userInput;
		if (userInput < aMinInputValue || userInput > aMaxInputValue || std::cin.fail())
		{
			userInput = -200;
			std::cin.clear(); //Clears the stream buffer.
			std::cin.ignore(1000); //Clears the input field.
		}

		return userInput;
	}


	//Thank Linus for telling me the altenative way of using a for loop.
	void ToLower(std::string& someValue)
	{
		//The below loop was written based of this article on how to lower case a character in C++
		//Source: https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/

		for (int i = 0; i < someValue.size(); i++)
		{
			someValue[i] = tolower(someValue[i]);
		}

	}

	std::string GetUserInput(std::string someAcceptablePhrases[], int anArraySize)
	{
		std::string userInput;
		std::cin >> userInput;
		//Based of this article on how to get the size of an array: 
		//https://www.educative.io/edpresso/how-to-find-the-length-of-an-array-in-cpp
		//Doesnt work anymore..
		//anArraySize = *(&acceptablePhrases + 1) - acceptablePhrases;

		std::cout << anArraySize;

		ToLower(userInput);

		for (int i = 0; i < anArraySize; i++)
		{
			if (userInput == someAcceptablePhrases[i])
			{
				if (userInput == someAcceptablePhrases[i])
				{
					game::errorMessage = userInput;

					return userInput;
				}
			}
		}



		userInput = "NaN";
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
		return -200;
	}
}