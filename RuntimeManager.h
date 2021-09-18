#pragma once
#include<iostream>
#include<iterator>
namespace RuntimeManagement
{

	enum class GameState
	{
		Start = -100,
		Menu = -99,
		Play = 0,
		Won = 10,
		Lost = 9,
		Error = -200,
		Exit = -1
	};

	enum class GameMode
	{
		None,
		RollADice,
		OddOrEven
	};


	int GetUserInputConstrainedOnValueRange(int aMinInputValue, int aMaxInputValue);
	int GetUserInput(int someAllowedValues[]);
	GameState GetGameStateFromInput(int someUserInput);
	GameMode GetGameModeFromInput(int someUserInput);
	void SelectGameMode();
	void OnGameEndMenu(std::string aMenuMessage);


	//The below variables NEED to have the extern keyword for the linker to work
	//Source: https://stackoverflow.com/a/9702142/10483209

	extern GameState currentGameState;
	extern GameState previousGameState;
	extern GameMode currentGameMode;
	extern std::string errorMessage;
	extern std::string currentGameModeName;

	 
}