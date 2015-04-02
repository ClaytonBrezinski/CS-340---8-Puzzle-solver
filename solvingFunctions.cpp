#include "Header.h"

void solvingFunctions:: depthFirstSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int depth)
{
	pushCurrentOrientation(topRow, middleRow, bottomRow);

	bool result = depthSolutionSearch(topRow, middleRow, bottomRow, ZeroPos, 0, depth);
	if (result != true)
	{
		cout << "goal orientation not achieved" << endl;
	}
	
}
void solvingFunctions:: breadthFirstSearch()
{
	//pushCurrentOrientation(topRow, middleRow, bottomRow);
}
void solvingFunctions:: bestFirstTiles()
{
	//pushCurrentOrientation(topRow, middleRow, bottomRow);
}
void solvingFunctions:: bestFirstMoves()
{
	//pushCurrentOrientation(topRow, middleRow, bottomRow);
}
void solvingFunctions:: bestFirstHeuristic(int heuristic)
{
	//pushCurrentOrientation(topRow, middleRow, bottomRow);
}
int solvingFunctions:: tilesOutOfPlace()
{
	return 0;
}

void solvingFunctions::pushCurrentOrientation(string topRow, string middleRow, string bottomRow)
{
	if (comparePrevousOrientations(topRow, middleRow, bottomRow))
	{
		string currentOrientation = topRow + middleRow + bottomRow;
		prevousOrientations[orientationSize] = currentOrientation;
		orientationSize++;
	}
	
	//else the orientation is already present
}
bool solvingFunctions:: comparePrevousOrientations(string topRow, string middleRow, string bottomRow)
{
	string currentOrientation = topRow + middleRow + bottomRow;
	for (int i = 0; i < orientationSize ; i++)
	{
		string temp = prevousOrientations[i];
		if (temp == currentOrientation)
		{
			return false;
		}
	}
	return true;
}
bool solvingFunctions:: depthSolutionSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int depth, int MaxDepth)
{
	pushCurrentOrientation(topRow, middleRow, bottomRow);
	string currentOrientation = topRow + middleRow + bottomRow;
	if (currentOrientation == goalOrientation)
	{
		cout << "goal orientation achieved" << endl;
		printout(topRow, middleRow, bottomRow);
		return true; // if solution was found return true
		// have print out functions here
		exit(0);
	}
	/*
	Make sure the depth is no larger than the users desired depth
	if so, increment depth and continue
	if not do not continue on from this depth
	*/
	if (depth <= MaxDepth)
	{ 
		depth++;
		/* Determine which positions you can swap with*/
		int swapPositions[4];
		for (int i = 0; i < 4; i++)
		{
			swapPositions[i] = -10;
		}
		ZeroPos = locateZero(topRow, middleRow, bottomRow); // redundant but a good measure
		determineSwapOptions(topRow, middleRow, bottomRow, ZeroPos, swapPositions);

		/*
		Determine where the zero is located then where each swap position is located
		once each swap location is determined, swap the nodes and call the function again
		*/
		int j = 0;
		if (ZeroPos >= 3 && ZeroPos < 6)
		{
			// Zero Location: middle row

			while (swapPositions[j] != -10 && j < 4)
			{
				string tempTop, tempMiddle, tempBottom;
				tempTop = topRow;
				tempMiddle = middleRow;
				tempBottom = bottomRow;

				if (swapPositions[j] >= 3 && swapPositions[j] < 6)
				{
					// Swap Node Location: middle row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 3;

					int tempSwapNodePosition = swapPositions[j] - 3;
					swap(tempMiddle, tempMiddle, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
				{
					// Swap Node Location: bottom row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 3;

					int tempSwapNodePosition = swapPositions[j] - 6;
					swap(tempMiddle, tempBottom, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else
				{
					// Swap Node Location: top row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 3;

					int tempSwapNodePosition = swapPositions[j];
					swap(tempMiddle, tempTop, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}

				j++;
			}
			
		}
		else if (ZeroPos >= 6 && ZeroPos < 9)
		{
			// Zero Location: bottom row
			while (swapPositions[j] != -10 && j < 4)
			{
				string tempTop, tempMiddle, tempBottom;
				tempTop = topRow;
				tempMiddle = middleRow;
				tempBottom = bottomRow;

				if (swapPositions[j] >= 3 && swapPositions[j] < 6)
				{
					// Swap Node Location: middle row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 6;

					int tempSwapNodePosition = swapPositions[j] - 3;
					swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
				{
					// Swap Node Location: bottom row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 6;

					int tempSwapNodePosition = swapPositions[j] - 6;
					swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else
				{
					// Swap Node Location: top row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
					tempZeroPos = tempZeroPos - 6;

					int tempSwapNodePosition = swapPositions[j];
					swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}

				j++;
			}
			
		}
		else
		{
			// Zero Location: top row

			while (swapPositions[j] != -10 && j < 4)
			{
				string tempTop, tempMiddle, tempBottom;
				tempTop = topRow;
				tempMiddle = middleRow;
				tempBottom = bottomRow;

				if (swapPositions[j] >= 3 && swapPositions[j] < 6)
				{
					// Swap Node Location: middle row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

					int tempSwapNodePosition = swapPositions[j] - 3;
					swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
				{
					// Swap Node Location: bottom row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

					int tempSwapNodePosition = swapPositions[j] - 6;
					swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}
				else
				{
					// Swap Node Location: top row
					int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

					int tempSwapNodePosition = swapPositions[j];
					swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
					if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
					{
						tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
						depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth);
					}
				}

				j++;
			}
			
		}

	}
	return false; // if the solution was not found return false
}
void solvingFunctions:: determineSwapOptions(string topRow, string middleRow, string bottomRow, int ZeroPos, int swapPositions[])
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