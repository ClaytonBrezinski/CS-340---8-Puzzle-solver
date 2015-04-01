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
using namespace std;

/* variables */
const string goalOrientation = "123405678";



/* regular functions */
char readIn();
void functionCaller(char choice);

/* solving functions */
void depthFirstSearch();
void breadthFirstSearch();
void bestFirstTiles();
void bestFirstMoves();
void bestFirstHeuristic(int heuristic);
int tilesOutOfPlace();