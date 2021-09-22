#include "Hasardspel.h"
#include"RollADice.h"
#include "OddOrEven.h"


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
	User::currentCapitalAmm = 10;
	bool isGameRunning = true;







	if (isGameRunning)
		while (isGameRunning)
		{
			if (!User::HasCapital())
			{

				game::currentGameState = game::GameState::Exit;
				system("CLS");
				std::cout << "You have ran out of cash! Proceeding to exit." << std::endl;
				system("pause");
			}

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
						std::cout << "(Type the following to proceed)[Exit|Play] ";
						std::string menuSelectionIndexes[] = { "play", "exit" };
						std::string input = game::GetUserInput(menuSelectionIndexes, 4);
						game::currentGameState = game::GetGameStateFromInput(input == "play" ? 0 : -1);
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
									OddOrEven::PlayGame();
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
						
						User::EarnCapital(game::currentGameMode);
						game::OnGameEndMenu("Game Won! Congrats!");

						break;
					}
				case game::GameState::Lost:
					{
						User::PayCapital();
						if (User::HasCapital())
						{
							game::OnGameEndMenu("Game Lost! Shame!...");
						}
						else
						{
							std::cout << "Game Lost! Shame...";
							system("pause");
						}
						break;
					}
				case game::GameState::Exit:
					{
						isGameRunning = false;
						break;
					}
				case game::GameState::Error:
					{
						system("CLS");
						std::cout << game::errorMessage << std::endl;
						game::currentGameState = game::previousGameState;
						system("pause");
						break;
					}

			}

		}
}









int main()
{
	Engine::OnGameRuntime();
}
