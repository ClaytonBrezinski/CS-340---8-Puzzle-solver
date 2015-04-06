#include "Header.h"

char readIn(string& topRow, string& middleRow, string& bottomRow)
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
	string input;
	inData >> input;

	topRow = input[0];
	topRow += input[1];
	topRow += input[2];

	middleRow = input[3];
	middleRow += input[4];
	middleRow += input[5];

	bottomRow = input[6];
	bottomRow += input[7];
	bottomRow += input[8];

	/* Determine what method the user wants to */
	char choice = 'W';
	while (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'a' && choice != 'b' && choice != 'c' && choice != 'Q' && choice != 'q')
	{
		cout << " If at any time during the information input phase you want to exit, please press Q " << endl;
		cout << " Please indicate what strategy you would like to solve the 8 - puzzle with: " << endl;
		cout << "A - Depth first" << endl << "B - Breadth first " << endl << " C - Best first" << endl;
		cin >> choice;
	}
	if (choice == 'Q' || choice == 'q')
	{
		cout << "exiting now" << endl;
		exit(0);
	}
	if (choice == 'C' || choice == 'c')
	{
		while (choice != 'D' && choice != 'E' && choice != 'F' && choice != 'd' && choice != 'e' && choice != 'f' && choice != 'Q' && choice != 'q')
		{
			cout << " Please indicate the best first strategy you would like to use" << endl;
			cout << "depth in search space + " << endl;
			cout << "D - Number of tiles out of place" << endl << "E - minimum number of moves to reach the goal state  " << endl << "  F - heuristic" << endl;
			cin >> choice;
		}
		if (choice == 'Q' || choice == 'q')
		{
			cout << "exiting now" << endl;
			exit(0);
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
		cout << "error in functions.cpp readIn" << endl;
	}
	else if (choice == 'd')
	{
		choice = 'D';
	}
	else if (choice == 'e')
	{
		choice = 'E';
	}
	else if (choice == 'f')
	{
		choice = 'F';
	}
	return choice;
}
void solvingFunctions:: functionCaller(char choice, string topRow, string middleRow, string bottomRow, int ZeroPos)
{
	switch (choice)
	{
	case 'A':
	{
		int depth;
		cout << " Please enter the depth at which you want the search to go: " << endl;
		cin >> depth;
		depthFirstSearch(topRow, middleRow, bottomRow, ZeroPos, depth);
		break;
	}
	case 'B': breadthFirstSearch();
	case 'C': cout << "error in switch" << endl;
	case 'D':
	{
		bestFirstTiles(topRow, middleRow, bottomRow, ZeroPos);
		break;
	}
	case 'E':
	{
		bestFirstMoves(topRow, middleRow, bottomRow, ZeroPos);
		break;
	}
	case 'F':
	{
		//int heuristic, totDist, seq;
		//totDist = totalDistance();
		//seq = sequenceScore();
		//heruistic = totdist + 3*seq;
		//bestFirstHeuristic(heuristic);
		//bestFirstHeuristic(heuristic);
		break;
	}
	}
}

int locateZero(string topRow, string middleRow, string bottomRow)
{
	for (int i = 0; i < 3; i++)
	{
		if (topRow[i] == '0')
		{
			return i;
		}
		else if (middleRow[i] == '0')
		{
			int result = i + 3 ;
			return result;
		}
		else if (bottomRow[i] == '0')
		{
			int result = i + 6 ;
			return result;
		}
	}
	return 10; // error has occured
}
int locateZero(string whole)
{
	for (int i = 0; i < 9; i++)
	{
		if (whole[i] == '0')
		{
			return i;
		}
	}
	return 10;	// error has occured
}
void swap(string& firstLevel, string& secondLevel, int firstPosition, int secondPosition)
{
	char temp = firstLevel[firstPosition];
	firstLevel[firstPosition] = secondLevel[secondPosition];
	secondLevel[secondPosition] = temp;
}
void printout(string topRow, string middleRow, string bottomRow)
{
	int zeroPos = locateZero(topRow, middleRow, bottomRow);
	for (int i = 0; i < 3; i++)
	{
		if (i == zeroPos)
		{
			cout << "_" << " ";
		}
		else
		{
			cout << topRow[i] << " ";
		}
	}
	cout << endl;

	int tempA = zeroPos - 3;
	for (int i = 0; i < 3; i++)
	{
		
		if (i == tempA)
		{
			cout << "_" << " ";
		}
		else
		{
			cout << middleRow[i] << " ";
		}
	}
	cout << endl;

	int tempB = zeroPos - 6;
	for (int i = 0; i < 3; i++)
	{
		if (i == tempB)
		{
			cout << "_" << " ";
		}
		else
		{
			cout << bottomRow[i] << " ";
		}
	}
	cout << endl;

}
void printout(string whole)
{
	int zeroPos = locateZero(whole);
	for (int i = 0; i < 9; i++)
	{
		if (i == zeroPos )
		{
			cout << "_" << " ";
		}
		else
		{
			cout << whole[i] << " ";
		}
		if (i == 2 || i == 5)
		{
			cout << endl;
		}
	}
	
}