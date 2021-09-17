#pragma once
#include <iostream>
#include <stdlib.h>

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
	GameState currentGameState;
	GameState previousGameState;
	GameMode currentGameMode;
	std::string errorMessage;
	std::string currentGameModeName;
}