

#include <iostream>
#include "Hasardspel.h"
#include"RollADice.h"
#include "Utility.h"
#include <stdlib.h>


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





void PrintIntroduction()
{
	std::cout << "Welcome to Scuffed Enjoyment AB's Casino Plaza, a place full of enjoyment and profit! \n";
	std::cout << "Here you can play our wonderful gambling game to earn rewards! \n\n" << std::flush;
	system("pause");
	system("CLS");
}

//void PrintTutorial()
//{
//	std::cout << "The rules are simple!\n\n" << std::flush;
//	system("pause");
//	system("CLS");
//	std::cout << "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
//	std::cout << "If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n" << std::flush;
//	system("pause");
//	system("CLS");
//
//}

namespace game = RuntimeManagement;






void OnGameRuntime()
{

	game::currentGameState = game::GameState::Start;
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
					std::cout << "Type a number of the corresponding menu element to proceed!\n";
					std::cout << "Exit|Play\n-1|0\n";
					game::currentGameState = game::GetGameStateFromInput(game::GetUserInput(-1, 0));
					break;
				}
			case game::GameState::Exit:
				{
					isGameRunning = false;
					break;
				}

		}

	}
}









int main()
{
	OnGameRuntime();
}
