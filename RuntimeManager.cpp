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

		bool hasWonTooManyTimesInRollADice = User::HasEarningsReachedThreshold(1000, GameMode::RollADice);
		bool hasWonTooManyTimesInOddOrEven = User::HasEarningsReachedThreshold(1000, GameMode::OddOrEven);
		bool hasWonTooManyTimesInRollADiceLite = User::HasEarningsReachedThreshold(1000, GameMode::RollADiceLite);
		system("CLS");
		previousGameState = currentGameState;
		std::cout << "Select a Game mode!\n";
		//std::cout << "[RollADice|OddOrEven] ";
		std::cout << "[" <<
			(hasWonTooManyTimesInRollADice ? "Unavailable|" : "RollADice|") <<
			(hasWonTooManyTimesInOddOrEven ? "Unavailable|" : "OddOrEven|") <<
			(hasWonTooManyTimesInRollADiceLite ? "Unavailable|" : "RollADiceLite|") << "Menu|" << "Exit" << "]" << std::endl;




		std::string gameModeSelectionIndexes[] = { "rolladice","rolladicelite", "oddoreven", "exit", "menu"};
		std::string userInput = User::GetUserInput(gameModeSelectionIndexes, 4);

		errorMessage = "Invalid text detected. Please try again! (User Input:";
		errorMessage += userInput;
		errorMessage += ")";


		if (userInput == "menu")
		{
			currentGameState = GameState::Menu;
		}
		else if (userInput == "exit")
		{
			currentGameState = GameState::Exit;
		}
		else if (userInput == "rolladice" && !hasWonTooManyTimesInRollADice)
		{
			currentGameMode = GameMode::RollADice;
		}
		else if (userInput == "rolladicelite" && !hasWonTooManyTimesInRollADiceLite)
		{
			currentGameMode = GameMode::RollADiceLite;
		}
		else if (userInput == "oddoreven" && !hasWonTooManyTimesInOddOrEven)
		{
			currentGameMode = GameMode::OddOrEven;
		}
		else if (!hasWonTooManyTimesInOddOrEven && !hasWonTooManyTimesInRollADice)
		{
			currentGameState = GameState::Error;

		}

	}

	int CurrentGameModeEarningsMultiplier()
	{
		switch (currentGameMode)
		{

			case RuntimeManagement::GameMode::RollADice:
				return 2;
			case RuntimeManagement::GameMode::OddOrEven:
				return 3;
			case RuntimeManagement::GameMode::RollADiceLite:
				return 4;
			default:
				return 1;

		}
	}




	void OnGameEndMenu(std::string aMenuMessage)
	{
		std::cout << aMenuMessage;

		if (User::HasEarningsReachedThreshold(1000, currentGameMode))
		{
			std::cout << std::endl;
			std::cout << "You have earned too much money from this gamemode! Returning to menu." << std::endl;
			system("pause");
			currentGameMode = GameMode::None;
			currentGameState = GameState::Menu;
			return;
		}

		std::cout << "[Continue|Menu|Quit] ";
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
	bool rollADiceLite_firstPlaythrough = true;

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
			case GameMode::RollADiceLite:
				{
					result = rollADiceLite_firstPlaythrough;
					rollADiceLite_firstPlaythrough = false;
				}

		}

		return result;
	}

	void DebugPrint(std::string someText)
	{
		std::cout << "[DebugLog]:" << someText << std::endl;
	}






}


