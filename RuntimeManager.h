#pragma once
#include<iostream>
#include<algorithm>
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


	int GetConstrainedNumericalUserInput(int aMinInputValue, int aMaxInputValue);
	int GetNumericalUserInput(int someAllowedValues[]);
	std::string GetUserInput(std::string someAcceptablePhrases[], int anArraySize);
	//Below method was commented out because its implementation was removed (see implementation for more info).
	//std::string ToLower(std::string someValue);
	GameState GetGameStateFromInput(int someUserInput);
	GameMode GetGameModeFromInput(int someUserInput);
	void OnGameModeSelection();
	void OnGameEndMenu(std::string aMenuMessage);



	//The below variables NEED to have the extern keyword for the linker to work
	//Source: https://stackoverflow.com/a/9702142/10483209

	extern GameState currentGameState;
	extern GameState previousGameState;
	extern GameMode currentGameMode;
	extern std::string errorMessage;


	 
}