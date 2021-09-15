

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
	std::cout << "Here you can play our wonderful gambling game to earn rewards! \n\n" << std::flush;
	system("pause");
	system("CLS");
}

void PrintTutorial()
{
	std::cout << "The rules are simple! \n" << std::flush;
	system("pause");
	system("CLS");
	std::cout << "Simply write a number of your choice when asked. Once you have written down a number, two dice rolls will thrown! \n";
	std::cout << "If the resulting number of these two dice rolls is the same as what you have written down, you win the game! \n\n" << std::flush;
	system("pause");
	system("CLS");

}

void OnGameRuntime()
{
	PrintIntroduction();
	PrintTutorial();

	bool isGameRunning = true;
	int currentGameState = 0;
	int previousGameState;

	int userInputValue;
	int generatedValue;

	const char* errorMessage = "Invalid Input!";



	while (isGameRunning)
	{
		switch (currentGameState)
		{
		case 0:
		{
			errorMessage = "Invalid Button Selection! Try again!";
			std::cout << "1 - Play|-1 - Exit\n";
			previousGameState = currentGameState;
			currentGameState = ParseCommand(-1, 1);
			system("CLS");
			break;
		}
		case -1:
		{
			isGameRunning = false;
			break;
		}

		case 1:
		{
			std::cout << "Write down a number between 1 and 12: ";
			previousGameState = currentGameState;
			userInputValue = ParseCommand(1, 12);

			if (userInputValue == -2)
			{
				errorMessage = "Inputed value is not between 1 and 12! Try again!";
				currentGameState = userInputValue;
				system("CLS");
				break;
			}

			generatedValue = GenerateResult();
			currentGameState = userInputValue == generatedValue ? 10 : 9;
			system("CLS");
			std::cout << "The dice yielded " << generatedValue << ", making " << userInputValue << (userInputValue == generatedValue ? " equal " : " not equal ") << "to " << generatedValue << "!\n";
			break;
		}
		case 10:
			errorMessage = "Invalid Button Selection! Try again!";
			std::cout << "Congratulations! You Won!\n";
			std::cout << "1 - Play Again|-1 - Exit\n";
			previousGameState = currentGameState;
			currentGameState = ParseCommand(-1, 1);
			system("CLS");
			break;

		case 9:
		{
			std::cout << "Shame... try again!\n\n" << std::flush;
			system("pause");
			system("CLS");
			currentGameState = 1;
			break;
		}

		case -2:
			std::cout << errorMessage << "\n";
			errorMessage = "";
			currentGameState = previousGameState;
			break;

		}
	}
}

int ParseCommand(int aMinInputValue, int aMaxInputValue)
{
	int userInput;
	std::cin >> userInput;

	if (std::cin.bad())
	{
		userInput = -1;
		std::cin.ignore(1000);
	}

	if (userInput < aMinInputValue || userInput > aMaxInputValue)
	{
		userInput = -2;
	}

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
