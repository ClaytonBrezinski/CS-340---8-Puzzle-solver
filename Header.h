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
const string goalOrientation = "123804765";

struct treeNodes
{
	string orientation;
	treeNodes* parent;
};

/* regular functions */
char readIn(string& topRow, string& middleRow, string& bottomRow);

int locateZero(string topRow, string middleRow, string bottomRow);
int locateZero(string whole);
void swap(string& firstLevel, string& secondLevel, int firstPosition, int secondPosition);
void printout(string topRow, string middleRow, string bottomRow);
void printout(string whole);
/* solving functions */

class solvingFunctions
{
public:
	array<string, 19999> prevousOrientations;
	int orientationSize = 0;
	array<treeNodes, 10000> tree;	//tree of 10,000 treeNodes
	void functionCaller(char choice, string topRow, string middleRow, string bottomRow, int ZeroPos);
private:
	void depthFirstSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int depth);
	void breadthFirstSearch();
	void bestFirstTiles();
	void bestFirstMoves();
	void bestFirstHeuristic(int heuristic);
	int tilesOutOfPlace();

	void pushCurrentOrientation(string topRow, string middleRow, string bottomRow);
	bool comparePrevousOrientations(string topRow, string middleRow, string bottomRow);
	bool depthSolutionSearch(string topRow, string middleRow, string bottomRow, int ZeroPos, int depth, int MaxDepth);
	void determineSwapOptions(string topRow, string middleRow, string bottomRow, int ZeroPos, int swapPositions[]);
};