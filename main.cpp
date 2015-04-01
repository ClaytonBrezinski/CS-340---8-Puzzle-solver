#include "Header.h"

int main()
{
	stack<string> prevousOrientations;
	array<treeNodes, 10000> tree;	//tree of 10,000 treeNodes
	string topRow, middleRow, bottomRow;
	int zeroPosition;


	char readInChoice;
	readInChoice = readIn(topRow, middleRow, bottomRow);
	zeroPosition = locateZero(topRow, middleRow, bottomRow);
	//functionCaller();

	printout(topRow, middleRow, bottomRow);
	printout(goalOrientation);
	
	return 0;
};