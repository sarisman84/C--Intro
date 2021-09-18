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

	int GetUserInputConstrainedOnValueRange(int aMinInputValue, int aMaxInputValue)
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

	int GetUserInput(int someAllowedValues[])
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

	void SelectGameMode()
	{
		system("CLS");
		previousGameState = currentGameState;
		std::cout << "Select a Game mode!\n";
		std::cout << "Roll A Dice|Odd Or Even\n     1     |     2     \n";
		int gameModeSelectionIndexes[] = { 1, 2 };
		int userInput = GetUserInput(gameModeSelectionIndexes);
		if (userInput == -200)
		{
			currentGameState = GameState::Error;
			return;
		}
		currentGameMode = GetGameModeFromInput(userInput);
	}


	void OnGameEndMenu(std::string aMenuMessage)
	{
		std::cout << aMenuMessage << "\n";
		std::cout << "Continue|Play Other Gamemode|Exit\n    0   |         1         |  -1  \n";
		int menuSelectionIndexes[] = { 0, 1, -1 };

		int userInput = GetUserInput(menuSelectionIndexes);
		if (userInput == 1)
		{
			currentGameMode = GameMode::None;
			currentGameState = GameState::Play;
			return;
		}

		currentGameState = GetGameStateFromInput(userInput);

	}





}


