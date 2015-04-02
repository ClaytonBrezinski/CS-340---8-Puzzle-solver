/*
student name : Clayton Brezinski
student # : 200220989
assignment: 4 - 8 puzzle solver
date written : April 3rd 2015

input format: 012345678
looks like this in the game: _ 1 2
							 3 4 5
							 6 7 8
0 being the empty space, will change it later for correct input.
*/

#include <iostream> 
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <array>
using namespace std;

/* variables */
const string goalOrientation = "123405678";

struct treeNodes
{
	string orientation;
	treeNodes* parent;
};

/* regular functions */
char readIn(string& topRow, string& middleRow, string& bottomRow);
void additionalReadIn(char readInChoice);
void functionCaller(char choice);
int locateZero(string topRow, string middleRow, string bottomRow);
int locateZero(string whole);
void swap(string& firstLevel, string& secondLevel, int firstPosition, int secondPosition);
void printout(string topRow, string middleRow, string bottomRow);
void printout(string whole);
/* solving functions */
void depthFirstSearch(int depth);
void breadthFirstSearch();
void bestFirstTiles();
void bestFirstMoves();
void bestFirstHeuristic(int heuristic);
int tilesOutOfPlace();

void depthSolutionSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int& depth);
void determineSwapOptions(string topRow, string middleRow, string bottomRow, int ZeroPos, int swapPositions[]);