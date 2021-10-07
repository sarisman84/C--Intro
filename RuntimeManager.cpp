#include "Roullete.h"

namespace RuntimeManagement
{

	const int maximumEarningsThreshold = 10000;
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

		bool hasWonTooManyTimesInRollADice = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::RollADice);
		bool hasWonTooManyTimesInOddOrEven = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::OddOrEven);
		bool hasWonTooManyTimesInRollADiceLite = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::RollADiceLite);
		bool hasWonTooManyTimesInGuessADoor = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::GuessADoor);
		bool hasWonTooManyTimesInRoullete = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::Roullete);
		bool hasWonToManyTimesInDebug = User::HasEarningsReachedThreshold(maximumEarningsThreshold, GameMode::Debug);
		system("CLS");
		previousGameState = currentGameState;
		std::cout << "Select a Game mode!\n";
		//std::cout << "[RollADice|OddOrEven] ";
		std::cout << "[" <<
			(hasWonTooManyTimesInRollADice ? "Unavailable|" : "RollADice|") <<
			(hasWonTooManyTimesInOddOrEven ? "Unavailable|" : "OddOrEven|") <<
			(hasWonTooManyTimesInRollADiceLite ? "Unavailable|" : "RollADiceLite|") <<
			(hasWonTooManyTimesInGuessADoor ? "Unavailable|" : "GuessADoor|") <<
			(hasWonTooManyTimesInRoullete ? "Unavailable|" : "Roullete|") << "Menu|" << "Exit" << "]" << std::endl;



		const std::string rollADiceGamemode = "rolladice";
		const std::string rollADiceLiteGamemode = "rolladicelite";
		const std::string oddorEvenGamemode = "oddoreven";
		const std::string guessADoorGamemode = "guessadoor";
		const std::string roulleteGamemode = "roullete";
		const std::string exitButton = "exit";
		const std::string menuButton = "menu";
		const std::string debugButton = "debug";
		std::array<std::string, 20> gameModeSelectionIndexes = { rollADiceGamemode,rollADiceLiteGamemode, oddorEvenGamemode, guessADoorGamemode, exitButton,menuButton, roulleteGamemode, debugButton };
		std::string userInput = User::GetUserInput(gameModeSelectionIndexes);

		errorMessage = "Invalid text detected. Please try again! (User Input:";
		errorMessage += userInput;
		errorMessage += ")";


		if (userInput == menuButton)
		{

			currentGameState = GameState::Menu;
		}
		else if (userInput == exitButton)
		{
			currentGameState = GameState::Exit;
		}
		else if (userInput == rollADiceGamemode && !hasWonTooManyTimesInRollADice)
		{
			currentGameMode = GameMode::RollADice;
		}
		else if (userInput == rollADiceLiteGamemode && !hasWonTooManyTimesInRollADiceLite)
		{
			currentGameMode = GameMode::RollADiceLite;
		}
		else if (userInput == oddorEvenGamemode && !hasWonTooManyTimesInOddOrEven)
		{
			currentGameMode = GameMode::OddOrEven;
		}
		else if (userInput == roulleteGamemode && !hasWonTooManyTimesInRoullete)
		{
			currentGameMode = GameMode::Roullete;
		}
		else if (userInput == guessADoorGamemode && !hasWonTooManyTimesInGuessADoor)
		{
			currentGameMode = GameMode::GuessADoor;
		}
		else if (userInput == debugButton)
		{
			system("cls");
			DebugPrint(std::string("Has Reached/Overtaken Hard Threshold ->" + hasWonToManyTimesInDebug
				? "Yes" : "No"));
			DebugPrint(std::string("Has Reached/Overtaken Soft Threshold ->" + User::HasEarningsReachedThreshold(500, currentGameMode) ? "Yes" : "No"));
			system("pause");
			currentGameMode = GameMode::Debug;
		}


	}

	int CurrentGameModeEarningsMultiplier()
	{
		int earningsMultiplier = 1;
		switch (currentGameMode)
		{

			case RuntimeManagement::GameMode::RollADice:
				{
					earningsMultiplier = 4;
					break;
				}

			case RuntimeManagement::GameMode::OddOrEven:
				{
					earningsMultiplier = 3;
					break;
				}

			case RuntimeManagement::GameMode::RollADiceLite:
				{
					earningsMultiplier = 3;
					break;
				}
			case RuntimeManagement::GameMode::GuessADoor:
				{
					earningsMultiplier = 2;
					break;
				}
			case RuntimeManagement::GameMode::Roullete:
				{
					earningsMultiplier = Roulette::GetBetMultiplier();
					break;
				}
		}
		return earningsMultiplier;
	}




	void OnGameEndMenu(std::string aMenuMessage)
	{
		std::cout << aMenuMessage;

		if (User::HasEarningsReachedThreshold(maximumEarningsThreshold, currentGameMode))
		{
			std::cout << std::endl;
			std::cout << "You have earned too much money from this gamemode! Returning to menu." << std::endl;
			system("pause");
			currentGameMode = GameMode::None;
			currentGameState = GameState::Menu;
			return;
		}

		std::cout << "[Continue|Menu|Quit] ";
		const std::string menuContinue = "continue", menuContinueShortcut = "c", menuBack = "menu", menuQuit = "quit";

		std::array<std::string, 20> menuSelectionIndexes = { menuContinue, menuContinueShortcut, menuBack, menuQuit };
		std::string userInput = User::GetUserInput(menuSelectionIndexes);
		if (userInput == menuBack)
		{
			currentGameMode = GameMode::None;
			currentGameState = GameState::Menu;
		}
		else if (userInput == menuContinue || userInput == menuContinueShortcut)
		{
			currentGameState = GameState::Play;
		}
		else if (userInput == menuQuit)
		{
			currentGameState = GameState::Exit;
		}
		else
		{
			system("cls");
			std::cout << errorMessage << std::endl;
			system("pause");
			OnGameEndMenu(aMenuMessage);
			return;
		}



	}

	bool rollADice_firstPlaythrough = true;
	bool oddOrEven_firstPlaythrough = true;
	bool rollADiceLite_firstPlaythrough = true;
	bool guessADoor_firstPlaythrough = true;
	bool roullete_firstPlaythrough = true;

	bool isCurrentUserNewToGameMode()
	{
		bool result = false;
		switch (currentGameMode)
		{
			case GameMode::RollADice:
				{
					result = rollADice_firstPlaythrough;
					rollADice_firstPlaythrough = false;
					break;
				}

			case GameMode::OddOrEven:
				{
					result = oddOrEven_firstPlaythrough;
					oddOrEven_firstPlaythrough = false;
					break;
				}
			case GameMode::RollADiceLite:
				{
					result = rollADiceLite_firstPlaythrough;
					rollADiceLite_firstPlaythrough = false;
					break;
				}
			case GameMode::GuessADoor:
				{
					result = guessADoor_firstPlaythrough;
					guessADoor_firstPlaythrough = false;
					break;
				}
			case GameMode::Roullete:
				{
					result = roullete_firstPlaythrough;
					roullete_firstPlaythrough = false;
					break;
				}

		}

		return result;
	}

	void DebugPrint(std::string someText)
	{
		std::cout << "[DebugLog]:" << someText << std::endl;
	}






}


