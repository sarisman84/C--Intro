#include "RuntimeManager.h"

namespace RuntimeManagement
{
	//The below variables NEED to be defined for the compiler to work.
	//Source: https://stackoverflow.com/a/9702142/10483209

	GameState currentGameState = GameState::Start;
	GameState previousGameState = currentGameState;
	GameMode currentGameMode = GameMode::RollADice;
	std::string errorMessage = "Invalid Input";

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
	std::string ToLower(std::string& someValue)
	{
		//The below loop was written based of this article on how to lower case a character in C++
		//Source: https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/

		for (char& i : someValue)
		{
			i = tolower(i);
		}
		return someValue;
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
					errorMessage = userInput;

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



	GameState GetGameStateFromInput(int someUserInput)
	{
		return static_cast<GameState>(someUserInput);
	}

	GameMode GetGameModeFromInput(int someUserInput)
	{
		return static_cast<GameMode>(someUserInput);
	}

	void OnGameModeSelection()
	{
		system("CLS");
		previousGameState = currentGameState;
		std::cout << "Select a Game mode!\n";
		std::cout << "[RollADice|OddOrEven] ";
		std::string gameModeSelectionIndexes[] = { "rolladice", "oddoreven" };
		std::string userInput = GetUserInput(gameModeSelectionIndexes, 2);
		std::cout << userInput;
		if (userInput == "rolladice")
		{
			currentGameMode = GameMode::RollADice;
		}
		else if (userInput == "oddoreven")
		{
			currentGameMode = GameMode::OddOrEven;
		}
		else
		{
			currentGameState = GameState::Error;
			system("pause");
		}
	}


	void OnGameEndMenu(std::string aMenuMessage)
	{
		std::cout << aMenuMessage << "[Continue|Play Other Games|Quit] ";
		std::string menuSelectionIndexes[] = { "continue", "play other games", "quit" };



		std::string userInput = GetUserInput(menuSelectionIndexes, 6);
		if (userInput == "play other games")
		{
			currentGameMode = GameMode::None;
			currentGameState = GameState::Play;
			return;
		}
		else if (userInput == "continue")
		{
			currentGameState = GameState::Play;
		}
		else if (userInput == "quit")
		{
			currentGameState = GameState::Exit;
		}
		else
		{
			currentGameState = GameState::Error;
		}



	}






}


