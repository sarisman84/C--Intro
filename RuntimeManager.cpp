#include "Player.h"

namespace RuntimeManagement
{
	//The below variables NEED to be defined for the compiler to work.
	//Source: https://stackoverflow.com/a/9702142/10483209

	GameState currentGameState = GameState::Start;
	GameState previousGameState = currentGameState;
	GameMode currentGameMode = GameMode::RollADice;
	std::string errorMessage = "Invalid Input";

	//Created by Marcus Dalh, is an altenative to rand()
	int RandomNumber(int aMinNumber, int aMaxNumber)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(aMinNumber, aMaxNumber); // define the range

		return distr(gen);
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
		std::string userInput = User::GetUserInput(gameModeSelectionIndexes, 2);
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
		std::cout << aMenuMessage << "[Continue|Menu|Quit] ";
		std::string menuSelectionIndexes[] = { "continue", "c", "menu", "quit" };



		std::string userInput = User::GetUserInput(menuSelectionIndexes, 4);
		if (userInput == "menu")
		{
			currentGameMode = GameMode::None;
			currentGameState = GameState::Menu;
		}
		else if (userInput == "continue" || userInput == "c")
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

	bool rollADice_firstPlaythrough = true;
	bool oddOrEven_firstPlaythrough = true;

	bool isCurrentUserNewToGameMode()
	{
		bool result = false;
		switch (currentGameMode)
		{
			case GameMode::RollADice:
				{
					result = rollADice_firstPlaythrough;
					rollADice_firstPlaythrough = false;
				}

			case GameMode::OddOrEven:
				{
					result = oddOrEven_firstPlaythrough;
					oddOrEven_firstPlaythrough = false;
				}
				
		}

		return result;
	}






}


