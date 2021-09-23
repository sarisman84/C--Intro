#pragma once
#include "Player.h"
namespace RollADice
{
	//Below line is based of this article
	//Source: https://www.tutorialspoint.com/cplusplus/cpp_return_arrays_from_functions.htm
	void GetInstructions(std::string (&anArray)[3]);
	int GenerateResult();
	void PlayGame();

}
