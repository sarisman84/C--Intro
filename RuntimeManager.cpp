#include "RuntimeManager.h"

namespace RuntimeManagement
{
	//The below variables NEED to be defined for the compiler to work.
	//Source: https://stackoverflow.com/a/9702142/10483209

	GameState currentGameState = GameState::Start;
	GameState previousGameState = currentGameState;
	GameMode currentGameMode = GameMode::RollADice;
	std::string errorMessage = "Invalid Input";
	std::string currentGameModeName = "NaN";

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

	std::string GetUserInput(std::string someAcceptablePhrases[], int anArraySize)
	{
		std::string userInput;
		std::cin >> userInput;
		//Based of this article on how to get the size of an array: 
		//https://www.educative.io/edpresso/how-to-find-the-length-of-an-array-in-cpp
		//Doesnt work anymore..
		//anArraySize = *(&acceptablePhrases + 1) - acceptablePhrases;

		std::cout << anArraySize;

		for (int i = 0; i < anArraySize; i++)
		{
			if (userInput == someAcceptablePhrases[i])
			{
				if (userInput == someAcceptablePhrases[i])
				{
					return userInput;
				}
			}
		}

		userInput = "NaN";
		return userInput;
	}

	//Below code is commented out as it is not allowed in the current assigment (Uppgift 2)

	//std::string ToLower(std::string someValue)
	//{
	//	//The below loop was written based of this article on how to lower case a character in C++
	//	//Source: https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/
	//	std::for_each(someValue.begin(), someValue.end(), [](char& c)
	//				  {
	//					  c = ::tolower(c);
	//				  });
	//	return someValue;
	//}

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
		std::string gameModeSelectionIndexes[] = { "RollADice", "OddOrEven" };
		std::string userInput = GetUserInput(gameModeSelectionIndexes, 2);
		std::cout << userInput;
		if (userInput == "RollADice")
		{
			currentGameMode = GameMode::RollADice;
		}
		else if (userInput == "OddOrEven")
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
		std::string menuSelectionIndexes[] = { "Continue", "Play Other Games", "Quit" };

		std::string userInput = GetUserInput(menuSelectionIndexes, 6);
		if (userInput == "Play Other Games")
		{
			currentGameMode = GameMode::None;
			currentGameState = GameState::Play;
			return;
		}
		else if (userInput == "Continue")
		{
			currentGameState = GameState::Play;
		}
		else if (userInput == "Quit")
		{
			currentGameState = GameState::Exit;
		}
		else
		{
			currentGameState = GameState::Error;
		}

	}






}


