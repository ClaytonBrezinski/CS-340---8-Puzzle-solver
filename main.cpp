#include "Header.h"

int main()
{
	stack<string> prevousOrientations;
	array<treeNodes, 10000> tree;	//tree of 10,000 treeNodes
	string topRow, middleRow, bottomRow;
	int zeroPosition;
	int usersNumberEntry;

	char readInChoice;
	readInChoice = readIn(topRow, middleRow, bottomRow);
	
	/*if (readInChoice == 'A' || readInChoice == 'D' || readInChoice == 'E' || readInChoice == 'F')
	{
		additionalReadIn(readInChoice);
	}
	else
	{
	breadthFirstSearch;
	}
	*/
	zeroPosition = locateZero(topRow, middleRow, bottomRow);

	depthSolutionSearch(topRow, middleRow, bottomRow, zeroPosition);
	//functionCaller();

	printout(topRow, middleRow, bottomRow);
	printout(goalOrientation);
	
	return 0;
};