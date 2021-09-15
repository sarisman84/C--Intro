

#include <iostream>
#include "Hasardspel.h"
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
	std::cout << "Welcome to Scuffed Enjoyment AB, a place full of enjoyment and profit! \n";
	std::cout << "Here you can play our wonderful gambling game to earn rewards! \n\n";
}

void PrintTutorial()
{
	std::cout << "The rules are simple! \n\n";
	system("pause");
	std::cout << "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
	std::cout << "If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n";
	system("pause");

}

void OnGameRuntime()
{
	PrintIntroduction();
	PrintTutorial();

	bool isGameRunning = true;
	int currentGameState = 0;
	while (isGameRunning)
	{
		switch (currentGameState)
		{
		case 0:
		{
			std::cout << "1 - Play|-1 - Exit\n";
			currentGameState = ParseCommand();
			break;
		}
		case -1:
		{
			isGameRunning = false;
			break;
		}

		case 1:
		{
			std::cout << "Write down a number: ";
			int inputValue = ParseCommand();
			int generatedValue = GenerateResult();
			std::cout << "The dice yielded " << generatedValue << ", making " << inputValue << (inputValue == generatedValue ? " equal " : " not equal ") << "to " << generatedValue << "!\n";
			currentGameState = inputValue == generatedValue ? 10 : 9;
			break;
		}
		case 10:
			currentGameState = -1;
			break;

		case 9:
		{
			std::cout << "Shame... try again!\n";
			currentGameState = 1;
			break;
		}

		}
	}
}

int ParseCommand()
{
	int userInput;
	std::cin >> userInput;
	return userInput;
}


int GenerateResult()
{
	int firstRoll = rand() % 6 + 1;
	int secondRoll = rand() % 6 + 1;
	return firstRoll + secondRoll;
}

int main()
{
	OnGameRuntime();
}
