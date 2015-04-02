#include "Header.h"

void depthFirstSearch(int depth)
{
	//depthSolutionSearch();
}
void breadthFirstSearch()
{

}
void bestFirstTiles()
{

}
void bestFirstMoves()
{

}
void bestFirstHeuristic(int heuristic)
{

}
int tilesOutOfPlace()
{
	return 0;
}


void depthSolutionSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int& depth)
{
	/* Determine which positions you can swap with*/
	int swapPositions[4];
	for (int i = 0; i < 4; i++)
	{
		swapPositions[i] = -10;
	}
	determineSwapOptions(topRow, middleRow, bottomRow, ZeroPos, swapPositions);
	
	/* 
	Determine where the zero is located then where each swap position is located
	once each swap location is determined, swap the nodes and call the function again
	*/
	int j = 0;
	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row
		int tempZeroPos = ZeroPos - 3;

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row
				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempMiddle, tempMiddle, tempZeroPos, tempSwapNodePosition);
				//depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos);
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempMiddle, tempBottom, tempZeroPos, tempSwapNodePosition);
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempMiddle, tempTop, tempZeroPos, tempSwapNodePosition);
			}

			j++;
		}
	}
	else if (ZeroPos >= 6 && ZeroPos < 9)
	{
		// Zero Location: bottom row
		int tempZeroPos = ZeroPos - 6;

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row
				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
			}

			j++;
		}
	}
	else
	{
		// Zero Location: top row
		int tempZeroPos = ZeroPos;

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row
				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
			}

-			j++;
		}
	}
	
	
}
void determineSwapOptions(string topRow, string middleRow, string bottomRow, int ZeroPos, int swapPositions[])
{
	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// middle row
		// swap options are: current row, row below it, row above it
		if (ZeroPos == 3)
		{
			// zero is in: middle left
			// swap with: top left, bottom left, middle center
			swapPositions[0] = 0;
			swapPositions[1] = 6;
			swapPositions[2] = 4;
		}
		else if (ZeroPos == 4)
		{
			// zero is in: middle center
			// swap with: top center, bottom center, middle left, middle right
			swapPositions[0] = 1;
			swapPositions[1] = 7;
			swapPositions[2] = 3;
			swapPositions[3] = 5;
		}
		else if (ZeroPos == 5)
		{
			// zero is in: middle right
			// swap with: top right, bottom right, middle center 
			swapPositions[0] = 2;
			swapPositions[1] = 8;
			swapPositions[2] = 4;
		}
		else
		{
			cout << " error in determineSwapOptions in middle row" << endl;
		}
	}
	else if (ZeroPos >= 6 && ZeroPos < 9)
	{
		// bottom row
		// swap options are: current row, row above it
		if (ZeroPos == 6)
		{
			// zero is in: zero is in: bottom left
			// swap with: middle left, bottom center
			swapPositions[0] = 3;
			swapPositions[1] = 7;
		}
		else if (ZeroPos == 7)
		{
			// zero is in: bottom center
			// swap with: middle center, bottom left, bottom right
			swapPositions[0] = 4;
			swapPositions[1] = 6;
			swapPositions[2] = 8;
		}
		else if (ZeroPos == 8)
		{
			// zero is in: bottom right
			// swap with: middle right, bottom center
			swapPositions[0] = 5;
			swapPositions[1] = 7;
		}
		else
		{
			cout << " error in determineSwapOptions in bottom row" << endl;
		}
	}
	else
	{
		//top row
		// swap options are: current row, row below it
		if (ZeroPos == 0)
		{
			// zero is in: top left
			// swap with: middle left and top center
			swapPositions[0] = 3;
			swapPositions[1] = 1;

		}
		else if (ZeroPos == 1)
		{
			// zero is in: top center
			// swap with: middle center, top left, top right
			swapPositions[0] = 4;
			swapPositions[1] = 0;
			swapPositions[2] = 2;
		}
		else if (ZeroPos == 2)
		{
			// zero is in: top right
			// swap with: middle right, top center
			swapPositions[0] = 5;
			swapPositions[1] = 1;
		}
		else
		{
			cout << " error in determineSwapOptions in top row" << endl;
		}
	}
}