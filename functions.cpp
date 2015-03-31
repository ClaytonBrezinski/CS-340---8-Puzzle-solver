#include "Header.h"

char readIn()
{
	ifstream inData;
	fstream outData;

	inData.open("input.txt");

	if (!inData)
	{
		cout << " you were not able to open the input file. Press any key to exit" << endl;
		string exit;
		cin >> exit;
	}

	/* read in the data from the text file and place into the correct rows*/
	int topRow, middleRom, bottomRow;
	string input;
	inData >> input;

	topRow += input[1];
	topRow += input[2];
	topRow += input[3];

	middleRom += input[4];
	middleRom += input[5];
	middleRom += input[6];

	bottomRow+= input[7];
	bottomRow += input[8];
	bottomRow += input[9];

	/* Determine what method the user wants to */
	char choice = 'q';
	while (choice != 'A' || choice != 'B' || choice != 'C' || choice != 'a' || choice != 'b' || choice != 'c')
	{
		cout << " Please indicate what strategy you would like to solve the 8 - puzzle with: " << endl;
		cout << "A - Depth first" << endl << "B - Breadth first " << endl << " C - Best first" << endl;
		cin >> choice;
	}
	if (choice == 'C' || choice == 'c')
	{
		while (choice != 'D' || choice != 'E' || choice != 'F' || choice != 'd' || choice != 'e' || choice != 'f')
		{
			cout << " Please indicate the best first strategy you would like to use" << endl;
			cout << "depth in search space + " << endl;
			cout << "D - Number of tiles out of place" << endl << "E - minimum number of moves to reach the goal state  " << endl << "  F - heuristic" << endl;
			cin >> choice;
		}

	}
	/* put in correct output format*/
	if (choice == 'a')
	{
		choice = 'A';
	}
	else if (choice == 'b')
	{
		choice = 'B';
	}
	else if (choice == 'c')
	{
		choice = 'C';
	}
	return choice;
}

void functionCaller(char choice)
{
	switch (choice)
	{
	case 'A': depthFirstSearch();
	case 'B': breadthFirstSearch();
	case 'C': cout << "error in switch" << endl;
	case 'D':
	{
		int tilesOutOfPlace();
		bestFirstTiles();
		break;
	}
	case 'E':
	{
		// need to continue on this
		bestFirstMoves();
		break;
	}
	case 'F':
	{
		int heuristic;
		cout << " Please enter a heuristic value" << endl;
		cin >> heuristic;

		bestFirstHeuristic(heuristic);
		break;
	}
	}
}

