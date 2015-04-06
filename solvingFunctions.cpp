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
void solvingFunctions:: bestFirstTiles(string topRow, string middleRow, string bottomRow, int ZeroPos)
{
	pushCurrentOrientation(topRow, middleRow, bottomRow);
	bool result = bestFirstTilesSolver(topRow, middleRow, bottomRow, ZeroPos);
	if (result != true)
	{
		cout << "goal orientation not achieved" << endl;
	}
}
void solvingFunctions:: bestFirstMoves(string topRow, string middleRow, string bottomRow, int ZeroPos)
{
	pushCurrentOrientation(topRow, middleRow, bottomRow);
	bool result = bestFirstMovesSolver(topRow, middleRow, bottomRow, ZeroPos);
	if (result != true)
	{
		cout << "goal orientation not achieved" << endl;
	}
}

void solvingFunctions::bestFirstHeuristic(string topRow, string middleRow, string bottomRow, int ZeroPos)
{
	pushCurrentOrientation(topRow, middleRow, bottomRow);
	bool result = bestFirstHeuristicSolver(topRow, middleRow, bottomRow, ZeroPos);
	if (result != true)
	{
		cout << "goal orientation not achieved" << endl;
	}
}


int solvingFunctions:: tilesOutOfPlace(string topRow, string middleRow, string bottomRow)
{
	/*
	look at tile, determine if it matches the solution
	if not: add to counter
	if it does: do nothing
	*/
	int counter = 0;
	string currentOrientation = topRow + middleRow + bottomRow;
	for (int i = 0; i < 9; i++)
	{
		if (currentOrientation[i] != goalOrientation[i])
		{
			counter++;
		}
	}
	return counter;
}

void solvingFunctions:: pushCurrentOrientation(string topRow, string middleRow, string bottomRow)
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
		/* Determine which positions you can swap with */
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
						if (depthSolutionSearch(tempTop, tempMiddle, tempBottom, tempZeroPos, depth, MaxDepth))
						{
							return true;
						}
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
bool solvingFunctions:: bestFirstTilesSolver(string topRow, string middleRow, string bottomRow, int ZeroPos)
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

	/* Determine swap options*/
	int swapPositions[4];
	for (int i = 0; i < 4; i++)
	{
		swapPositions[i] = -10;
	}
	ZeroPos = locateZero(topRow, middleRow, bottomRow); // redundant but a good measure
	determineSwapOptions(topRow, middleRow, bottomRow, ZeroPos, swapPositions);

	// determine which orientation will yield the lowest amount of tiles out of place
	int j = 0;
	int numTilesOutOfPlace[4];	//holder for amounts of moves
	for (int i = 0; i < 4; i++)
	{
		numTilesOutOfPlace[i] = -10;
	}

	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				numTilesOutOfPlace[j] = tilesOutOfPlace(tempTop, tempMiddle, tempBottom);
			}
			j++;
		}

	}
	// order the nodes from lowest amount of moves to the largest
	int a, b, c, d;
	int e, f, g, h;

	a = numTilesOutOfPlace[0];
	b = numTilesOutOfPlace[1];
	c = numTilesOutOfPlace[2];
	d = numTilesOutOfPlace[3];

	e = swapPositions[0];
	f = swapPositions[1];
	g = swapPositions[2];
	h = swapPositions[3];

	if (a > b)
	{
		swap(a, b);
		swap(e, f);		// a < b
	}
	if (c > d && d != -10)
	{
		swap(c, d);
		swap(g, h);		// c < d
	}
	if (c < a && c != -10)
	{
		swap(a, c);
		swap(e, g);		// a < c
	}
	if (d < b && d != -10)
	{
		swap(b, d);
		swap(f, h);		// b < d
	}
	if (b > c && c != -10)
	{
		swap(b, c);
		swap(f, g);
	}
	
	//good for trouble shooting
	numTilesOutOfPlace[0] = a;
	numTilesOutOfPlace[1] = b;
	numTilesOutOfPlace[2] = c;
	numTilesOutOfPlace[3] = d;
	

	swapPositions[0] = e;
	swapPositions[1] = f;
	swapPositions[2] = g;
	swapPositions[3] = h;



	j = 0;
	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempMiddle, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempMiddle, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempMiddle, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row
		
				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row


				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstTilesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}

			j++;
		}

	}
		return false; // if the solution was not found return false
}
bool solvingFunctions:: bestFirstMovesSolver(string topRow, string middleRow, string bottomRow, int ZeroPos)
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

	/* Determine swap options*/
	int swapPositions[4];
	for (int i = 0; i < 4; i++)
	{
		swapPositions[i] = -10;
	}
	ZeroPos = locateZero(topRow, middleRow, bottomRow); // redundant but a good measure
	determineSwapOptions(topRow, middleRow, bottomRow, ZeroPos, swapPositions);

	// determine which orientation will yield the lowest amount of moves to the goal orientation
	int j = 0;
	int movesToGoalState[4];	//holder for amounts of moves
	for (int i = 0; i < 4; i++)
	{
		movesToGoalState[i] = -10;
	}

	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				movesToGoalState[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
			}
			j++;
		}

	}
	// order the nodes from lowest amount of moves to the largest
	int a, b, c, d;
	int e, f, g, h;

	a = movesToGoalState[0];
	b = movesToGoalState[1];
	c = movesToGoalState[2];
	d = movesToGoalState[3];

	e = swapPositions[0];
	f = swapPositions[1];
	g = swapPositions[2];
	h = swapPositions[3];

	if (a > b)
	{
		swap(a, b);
		swap(e, f);		// a < b
	}
	if (c > d && d != -10)
	{
		swap(c, d);
		swap(g, h);		// c < d
	}
	if (c < a && c != -10)
	{
		swap(a, c);
		swap(e, g);		// a < c
	}
	if (d < b && d != -10)
	{
		swap(b, d);
		swap(f, h);		// b < d
	}
	if (b > c && c != -10)
	{
		swap(b, c);
		swap(f, g);
	}
	/* 
	good for trouble shooting 
	movesToGoalState[0] = a;
	movesToGoalState[1] = b;
	movesToGoalState[2] = c;
	movesToGoalState[3] = d;
	*/

	swapPositions[0] = e;
	swapPositions[1] = f;
	swapPositions[2] = g;
	swapPositions[3] = h;



	// perform the swaps based on the most efficient going before the lesser efficient
	j = 0;
	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempMiddle, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempMiddle, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempMiddle, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row


				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}

			j++;
		}

	}
	return false; // if the solution was not found return false
}
bool solvingFunctions:: bestFirstHeuristicSolver(string topRow, string middleRow, string bottomRow, int ZeroPos)
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

	/* Determine swap options*/
	int swapPositions[4];
	for (int i = 0; i < 4; i++)
	{
		swapPositions[i] = -10;
	}
	ZeroPos = locateZero(topRow, middleRow, bottomRow); // redundant but a good measure
	determineSwapOptions(topRow, middleRow, bottomRow, ZeroPos, swapPositions);

	// determine which orientation will yield the lowest amount of moves to the goal orientation
	int j = 0;
	int totalDistance[4];		// holder manhattan distance values
	int sequenceScoreHolder[4];	// holder for sequence score values
	for (int i = 0; i < 4; i++)
	{
		totalDistance[i] = -10;
		sequenceScoreHolder[i] = -10;
	}

	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);

			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempZeroPos = locateZero(topRow, middleRow, bottomRow);

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				totalDistance[j] = movesUntilGoalState(tempTop, tempMiddle, tempBottom);
				sequenceScoreHolder[j] = sequenceScore(tempTop, tempMiddle, tempBottom);
			}
			j++;
		}

	}

	int heuristic[4];
	for (int i = 0; i < 4; i++)
	{
		heuristic[i] = -10;
		if (totalDistance[i] != -10 && sequenceScoreHolder[i] != -10)
		{
			heuristic[i] = totalDistance[i] + sequenceScoreHolder[i];
		}
	}

	// order the nodes from lowest heuristic to the largest
	int a, b, c, d;
	int e, f, g, h;

	a = heuristic[0];
	b = heuristic[1];
	c = heuristic[2];
	d = heuristic[3];

	e = swapPositions[0];
	f = swapPositions[1];
	g = swapPositions[2];
	h = swapPositions[3];

	if (a > b)
	{
		swap(a, b);
		swap(e, f);		// a < b
	}
	if (c > d && d != -10)
	{
		swap(c, d);
		swap(g, h);		// c < d
	}
	if (c < a && c != -10)
	{
		swap(a, c);
		swap(e, g);		// a < c
	}
	if (d < b && d != -10)
	{
		swap(b, d);
		swap(f, h);		// b < d
	}
	if (b > c && c != -10)
	{
		swap(b, c);
		swap(f, g);
	}

	/*
	good for trouble shooting
	heuristic[0] = a;
	heuristic[1] = b;
	heuristic[2] = c;
	heuristic[3] = d;
	*/


	swapPositions[0] = e;
	swapPositions[1] = f;
	swapPositions[2] = g;
	swapPositions[3] = h;



	// perform the swaps based on the most efficient going before the lesser efficient
	j = 0;
	if (ZeroPos >= 3 && ZeroPos < 6)
	{
		// Zero Location: middle row

		while (swapPositions[j] != -10 && j < 4)
		{
			string tempTop, tempMiddle, tempBottom;
			tempTop = topRow;
			tempMiddle = middleRow;
			tempBottom = bottomRow;

			// given that the zero location is in the middle row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 3;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempMiddle, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempMiddle, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row

				int tempSwapNodePosition = swapPositions[j];
				swap(tempMiddle, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the bottom row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos - 6;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row

				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempBottom, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row
				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempBottom, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempBottom, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
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

			// given that the zero location is in the top row
			int tempZeroPos = locateZero(topRow, middleRow, bottomRow);
			tempZeroPos = tempZeroPos;

			if (swapPositions[j] >= 3 && swapPositions[j] < 6)
			{
				// Swap Node Location: middle row


				int tempSwapNodePosition = swapPositions[j] - 3;
				swap(tempTop, tempMiddle, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure

					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}

				}
			}
			else if (swapPositions[j] >= 6 && swapPositions[j] < 9)
			{
				// Swap Node Location: bottom row

				int tempSwapNodePosition = swapPositions[j] - 6;
				swap(tempTop, tempBottom, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}
			else
			{
				// Swap Node Location: top row
				int tempSwapNodePosition = swapPositions[j];
				swap(tempTop, tempTop, tempZeroPos, tempSwapNodePosition);
				if (comparePrevousOrientations(tempTop, tempMiddle, tempBottom))
				{
					tempZeroPos = locateZero(tempTop, tempMiddle, tempBottom); // redundant but a good measure
					if (bestFirstMovesSolver(tempTop, tempMiddle, tempBottom, tempZeroPos))
					{
						return true;
					}
				}
			}

			j++;
		}

	}
	return false; // if the solution was not found return false
}

int solvingFunctions:: sequenceScore(string topRow, string middleRow, string bottomRow)
{
	string currentOrientation = topRow + middleRow + bottomRow;
	int sequenceScoreCounter = 0;
	// if there is any value besides 0 in the center, + 1
	if (currentOrientation[4] != '0')
	{
		sequenceScoreCounter++;
	}
	// if a value that is not in the center, check if it has the proper successor based on clock wise format. If it does not + 2
	for (int i = 0; i < 9; i++)
	{
		if (i != 4)
		{
			bool correctSuccessor = properSuccessor(currentOrientation, currentOrientation[i], i);
			if (correctSuccessor == false)
			{
				sequenceScoreCounter = sequenceScoreCounter + 2;
			}
		}
	}
  return sequenceScoreCounter;
}
bool solvingFunctions:: properSuccessor(string currentOrientation, char value, int position)
{
	// determine the correct successor position and its associated value;
	int successorPos = successorPosition(position);
	char successorValue = currentOrientation[successorPos];

	// find the same value within the goalOrientation and determine its successor position
	int goalPos;
	for (int i = 0; i < 9; i++)
	{
		
		if (value == goalOrientation[i])
		{
			if (i != 4)
			{
				goalPos = i;
				break;
			}
			else
			{
				return false;
			}
		}
		
	}
	int goalSuccessorPos = successorPosition(goalPos);
	char goalSuccessorValue = goalOrientation[goalSuccessorPos];

	// if the value of the current orientations successory matches that of the goal orientations successor return true
	if (successorValue == goalSuccessorValue)
	{
		return true;
	}
	else
	{
		return false; 
	}
}
int solvingFunctions:: successorPosition(int position)
{
	// based on a clockwise format, return the clockwise position
	if (position == 0)
	{
		return 3;
	}
	else if (position == 1)
	{
		return 0;
	}
	else if (position == 2)
	{
		return 1;
	}
	else if (position == 3)
	{
		return 6;
	}
	else if (position == 6)
	{
		return 7;
	}
	else if (position == 7)
	{
		return 8;
	}
	else if (position == 8)
	{
		return 5;
	}
	else if (position == 5)
	{
		return 2;
	}
	return 10;	// error has occured
}

int solvingFunctions:: movesUntilGoalState(string topRow, string middleRow, string bottomRow)
{
	string currentOrientation = topRow + middleRow + bottomRow;
	int totalMoves = 0;
	/* 
	look at each square, if it is out of place when compared to the goal orientation
	determine how many moves it will take to get that square to the correct location
	*/
	for (int i = 0; i < 9; i++)
	{
		if (currentOrientation[i] != goalOrientation[i])
		{
			totalMoves += manhattanDistance(i, currentOrientation[i]);
		}
	}
	return totalMoves;
}
int solvingFunctions:: manhattanDistance(int currentSquarePosition, char squareValue)
{
	// determine the position of the goal square
	int goalSquareLocation;
	for (int i = 0; i < 9; i++)
	{
		if (squareValue == goalOrientation[i])
		{
			goalSquareLocation = i;
		}
	}
	// determine how many rows and column moves need to take place
	int difference;
	if (goalSquareLocation >= currentSquarePosition)
	{
		difference = goalSquareLocation - currentSquarePosition;
	}
	else
	{
		difference = currentSquarePosition - goalSquareLocation;
	}
	/*
	based on the current square position, first determine how many rows to go up or down
	once that is complete, determine how many columns the value needs to move
	return the sum of these two results.
	*/
	int temp = difference;
	int rowsToMove = temp / 3;
	int colsToMove = difference - rowsToMove * 3;
	int returnvalue = rowsToMove + colsToMove;
	return returnvalue;
}


