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
	
	string exit;
	cout << "Press any key then enter to exit" << endl;
	cin >> exit;
	return 0;
};