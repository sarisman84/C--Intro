#include "Hasardspel.h"
#include"StatisticsManager.h"
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
	std::cout << "Welcome to Scuffed Enjoyment AB's Twitch Casino, a place full of enjoyment and profit! \n";
	std::cout << "Here you can play our wonderful gambling game to earn rewards! \n\n" << std::flush;
	system("pause");
	system("CLS");
}










void Engine::OnGameRuntime()
{

	game::currentGameState = game::GameState::Start;
	game::currentGameMode = game::GameMode::None;
	User::currentCapitalAmm = 1000;
	bool isGameRunning = true;







	if (isGameRunning)
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
						if (!User::HasCapital())
						{

							game::currentGameState = game::GameState::Exit;
							system("CLS");
							std::cout << "You have ran out of cash! Proceeding to exit." << std::endl;
							system("pause");
						}

						system("CLS");
						game::previousGameState = game::currentGameState;
						std::cout << "Current amount of cash: " << User::currentCapitalAmm << std::endl << std::endl;
						Statistics::PrintCurrentStatistics();
						std::cout << std::endl;
						std::cout << "What do you want to do?" << std::endl;
						std::cout << "(Type the following to proceed)[Exit|Play] ";
						std::string menuSelectionIndexes[] = { "play", "exit" };
						std::string input = User::GetUserInput(menuSelectionIndexes, 4);
						game::currentGameState = game::GetGameStateFromInput(input == "play" ? 0 : input == "exit" ? -1 : -200);
						break;
					}
				case game::GameState::Play:
					{
						system("CLS");
						game::previousGameState = game::currentGameState;

						if (game::currentGameMode != game::GameMode::None)
						{
							if (!game::isCurrentUserNewToGameMode())
							{
								std::cout << "What do you want to do?" << std::endl;
								std::cout << "[Play|See Tutorial|Menu|Exit] ";
								std::string menuSelectionOptions[] = { "play","p","see tutorial", "tutorial", "exit", "quit", "menu" };
								std::string input = User::GetUserInput(menuSelectionOptions, 7);
								if (input == "menu")
								{
									game::currentGameState = game::GameState::Menu;
									break;
								}
								else if(input == "see tutorial" || input == "tutorial")
								{
									game::currentGameState = game::GameState::Tutorial;
									break;
								}
								else if (input == "exit" || input == "quit")
								{
									game::currentGameState = game::GameState::Exit;
									break;
								}
								else if (input == "NaN")
								{
									game::currentGameState = game::GameState::Error;
									break;
								}
							}
							else
							{
								game::currentGameState = game::GameState::Tutorial;
								break;
							}
						}

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
							case game::GameMode::RollADiceLite:
								{
									RollADiceLite::PlayGame();
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
				case game::GameState::Tutorial:
					{
						switch (game::currentGameMode)
						{
							case game::GameMode::RollADice:
								{

									std::string instructions[3];
									RollADice::GetInstructions(instructions);
									User::DisplayStringArrayToConsole(3, instructions);
									break;
								}
							case game::GameMode::OddOrEven:
								{
									std::string instructions[2];
									OddOrEven::GetInstructions(instructions);
									User::DisplayStringArrayToConsole(2, instructions);
									break;
								}
							case game::GameMode::RollADiceLite:
								{
									std::string instructions[3];
									RollADiceLite::GetInstructions(instructions);
									User::DisplayStringArrayToConsole(3, instructions);
									break;
								}
						}
						game::currentGameState = game::GameState::Play;
						break;
					}
				case game::GameState::Won:
					{


						User::hasUserWon = true;
						User::EarnCapital();
						Statistics::SaveCurrentGameStatistics();
						Statistics::PrintCurrentStatistics();
						game::OnGameEndMenu("Game Won! Congrats!");

						break;
					}
				case game::GameState::Lost:
					{
						User::hasUserWon = false;
						User::PayCapital();
						Statistics::SaveCurrentGameStatistics();
						Statistics::PrintCurrentStatistics();
						if (User::HasCapital())
						{
							game::OnGameEndMenu("Game Lost! Shame!...");
						}
						else
						{

							game::currentGameState = game::GameState::Exit;

							std::cout << "Game Lost! Shame...";
							system("pause");
							system("CLS");
							std::cout << "You have ran out of cash! Proceeding to exit." << std::endl;
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
