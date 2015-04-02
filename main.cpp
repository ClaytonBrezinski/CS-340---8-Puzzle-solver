#include "Header.h"

int main()
{
	solvingFunctions solvePuzzle;
	string topRow, middleRow, bottomRow;
	int zeroPosition;

	char readInChoice;
	readInChoice = readIn(topRow, middleRow, bottomRow);
	zeroPosition = locateZero(topRow, middleRow, bottomRow);
	
	solvePuzzle.functionCaller(readInChoice, topRow, middleRow, bottomRow, zeroPosition);
	
	return 0;
};