#include "Hasardspel.h"
#include"RollADice.h"


/*
	Todo:
	-Create a basic guessing game.
		-Create an introduction.
		-Create a tutorial that explains how the game works.
		-User has the ability to guess a random number that is constrained (i.e. not to big or small).
			-If the input number is wrong, display a message about it and let the User retry.
			-If the input number is correct,display a message about it and let the User decide to retry or exit the program.
		-Generate a random number by adding together two random results.
			-This generation happens after the User inputs a value.

*/

namespace game = RuntimeManagement;




void Engine::PrintIntroduction()
{
	std::cout << "Welcome to Scuffed Enjoyment AB's Casino Plaza, a place full of enjoyment and profit! \n";
	std::cout << "Here you can play our wonderful gambling game to earn rewards! \n\n" << std::flush;
	system("pause");
	system("CLS");
}










void Engine::OnGameRuntime()
{

	game::currentGameState = game::GameState::Start;
	game::currentGameMode = game::GameMode::None;
	bool isGameRunning = true;




	while (isGameRunning)
	{
		switch (game::currentGameState)
		{

			case game::GameState::Start:
				{
					PrintIntroduction();
					game::currentGameState = game::GameState::Menu;
					break;
				}
			case game::GameState::Menu:
				{
					game::previousGameState = game::currentGameState;
					std::cout << "Type a number of the corresponding menu element to proceed!\n";
					std::cout << "Exit|Play\n -1 | 0 \n";
					int menuSelectionIndexes[] = { -1,0 };
					game::currentGameState = game::GetGameStateFromInput(game::GetNumericalUserInput(menuSelectionIndexes));
					break;
				}
			case game::GameState::Play:
				{
					game::previousGameState = game::currentGameState;

					switch (game::currentGameMode)
					{
						case game::GameMode::RollADice:
							{
								RollADice::PlayGame();
								break;
							}
						case game::GameMode::OddOrEven:
							{
								break;
							}
						case game::GameMode::None:
							{
								game::OnGameModeSelection();
								break;
							}

					}
					break;
				}
			case game::GameState::Won:
				{
					/*
						Here reward player and give said player the option to either play again the same game mode
						or select a new game mode.
					*/
					game::OnGameEndMenu("Game Won! Congrats!");

					break;
				}
			case game::GameState::Lost:
				{

					game::OnGameEndMenu("Game Lost! Shame!...");

					break;
				}
			case game::GameState::Exit:
				{
					isGameRunning = false;
					break;
				}
			case game::GameState::Error:
				{
					std::cout << game::errorMessage;
					game::currentGameState = game::previousGameState;
					break;
				}

		}

	}
}









int main()
{
	Engine::OnGameRuntime();
}
