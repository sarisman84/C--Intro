#pragma once
#include<iostream>
#include<algorithm>
#include<random>
#include<array>
#include<string>

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
		Exit = -1,
		Tutorial = 100
	};

	enum class GameMode
	{
		None,
		RollADice,
		OddOrEven,
		RollADiceLite,
		GuessADoor,
		Roullete,
		Debug
	};



	//Below method was commented out because its implementation was removed (see implementation for more info).
	//std::string ToLower(std::string someValue);
	GameState GetGameStateFromInput(int someUserInput);
	GameMode GetGameModeFromInput(int someUserInput);
	/*Created by Marcus Dalh, is an altenative to rand()
	Selects a random number between a minimum (inclusive) and a maximum (inclusive) number.
	*/
	int RandomNumber(int aMinNumber, int aMaxNumber);
	void OnGameModeSelection();
	void OnGameEndMenu(std::string aMenuMessage);
	bool isCurrentUserNewToGameMode();
	int CurrentGameModeEarningsMultiplier();



	//The below variables NEED to have the extern keyword for the linker to work
	//Source: https://stackoverflow.com/a/9702142/10483209

	extern GameState currentGameState;
	extern GameState previousGameState;
	extern GameMode currentGameMode;
	extern std::string errorMessage;


	void DebugPrint(std::string someText);



}