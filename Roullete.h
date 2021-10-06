#pragma once
#include "Player.h"

namespace Roulette
{
	enum class BetType
	{
		Straight,
		Split,
		Corner,
		OddOrEven,
		Column,
		RedOrBlack
	};

	enum class SelectionType
	{
		User,
		Game,
		LegalOption,
		None,
		Invalid = -200
	};

	enum class NumberType
	{
		Odd,
		Even,
		Black,
		Red
	};

	


	void PlayGame();
	extern std::array<std::string, 20> userInstructions;
	bool TryGuessANumber();
	bool TryGuessTwoNumbersWithAConstraint();
	bool TryGuessACorner();
	bool TrySelectBetType(BetType &aValidBetType);
	int GetValidatedNumberThatIsAdjacent(std::array<std::array<int, 2>, 4> someLegalPositions, int aNewNumber);
	int GetBetMultiplier();
	std::array<std::array<int, 2>, 4> GetLegalPositions(int anOriginPoint);
	int Search(std::array<std::array<int, 3>, 13> aBoard, int anElementToFind);
	std::array<int, 2> GetIndex(std::array<std::array<int, 3>, 13> aBoard, int anElementToFindIndex);
	std::array < std::array <int, 2>, 4 > GetLegalNumbers(std::array<int, 2> aGridCoordinate);
	int GetValueFromPosition(std::array<int, 2> aPosition);
	bool IsPositionOutOfBounds(std::array<int, 2> aGridPosition);
	int GetRandomNumberFromRoulette();
	void DrawBoard();
	void SelectElementFromBoard(int aNumberToSelect, SelectionType aSelectionOwner);
}