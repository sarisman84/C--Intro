#include "Utility.h"
#include <iostream>

int RuntimeManagement::GetUserInput(int aMinInputValue, int aMaxInputValue)
{
	int userInput;
	std::cin >> userInput;
	if (userInput < aMinInputValue || userInput > aMaxInputValue || std::cin.fail())
	{
		userInput = -200;
		std::cin.clear(); //Clears the stream buffer.
		std::cin.ignore(1000); //Clears the input field.
	}

	return userInput;
}

RuntimeManagement::GameState RuntimeManagement::GetGameStateFromInput(int someUserInput)
{
	return static_cast<GameState>(someUserInput);
}

