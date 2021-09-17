#pragma once
#include<iostream>
namespace RuntimeManagement
{

	enum class GameState
	{
		Start = -100,
		Menu = -99,
		Play = 0,
		SelectGameMode,
		Won = 10,
		Lost = 9,
		Error = -200,
		Exit = -1
	};

	enum class GameMode
	{
		RollADice,
		OddOrEven
	};


	int GetUserInput(int aMinInputValue, int aMaxInputValue);
	GameState GetGameStateFromInput(int someUserInput);

	//The below variables NEED to have the extern keyword for the linker to work
	//Source: https://stackoverflow.com/a/9702142/10483209

	extern GameState currentGameState;
	extern GameState previousGameState;
	extern GameMode currentGameMode;
	extern const char* errorMessage;
	extern const char* currentGameModeName;

	 
}