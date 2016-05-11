/*
  solve.cpp: contains 'main' function.

*/

#include <iostream>

#include <cstring>
#include <cstdlib>
#include <unistd.h>

// 221 STUDENTS: You'll need to include any .hpp files of classes that
// you create and use here
#include "MazeState.hpp"
#include "SliderPuzzle.hpp"
#include "Sudoku.hpp"
#include "TextMaze.hpp"

#include "ArrayStack.hpp"
#include "LinkedListStack.hpp"
#include "UnsortedPriorityQueue.hpp"
#include "HeapPriorityQueue.hpp"

#include "LinkedListDict.hpp"
#include "AVLDict.hpp"
#include "LinearHashDict.hpp"
#include "DoubleHashDict.hpp"

using namespace std;

// Simple recursive function to print out a sequence of states from
// the start state to goal.
// length returns how many steps there were in the path to goal.
void printTraceTo(MazeState *goal, PredDict &seen, int &length) {
  // Should not be called with NULL
  if (goal==NULL) {
    cerr << "Error:  Do not call printSolution without a goal.\n";
    return;
  }

  // Find the state that we used to get to goal.
  MazeState *predecessor;
  seen.find(goal,predecessor);

  if (predecessor==NULL) {
    // Base Case:  If predecessor is NULL, then goal is the starting state.
    length = 0;
    cout << "Starting from this state:\n";
    goal->print(cout);
  } else {
    // Recursive Case:  Print solution to predecessor, then one step to goal.
    printTraceTo(predecessor, seen, length);
    length++;
    cout << "Step " << length << " leads to...\n";
    goal->print(cout);
  }
}

// This function does the actual solving.
void solveMaze(MazeState *start, BagOfMazeStates &active, PredDict &seen) {

  MazeState *state;
  MazeState *temp;

  active.add(start); // Must explore the successors of the start state.
  seen.add(start,NULL); // We've seen this state.  It has no predecessor.

  while (!active.is_empty()) {
    // Loop Invariants:
    // 'seen' contains the set of maze states that we know how to reach.
    // 'active' contains the set of maze states that we know how to reach,
    //    and from which there may be new states we haven't explored yet.

    state = active.remove();
    // Note:  Don't delete state when done, as this MazeState is also in seen

    // The following two lines are handy for debugging, or seeing what
    // the algorithm is doing.
    // 221 STUDENTS:  Comment these out when you want the program to
    // run at full speed!
    //cout << "Exploring State: \n";
    //state->print(cout);
    //usleep(20000);	// Pause for some microseconds, to let human read output

    if (state->isSolution()) {
      // Found a solution!
      cout << "***** Found a solution!!!!! ***** \n";
      int temp; // Throwaway variable to call recursive printTraceTo
      printTraceTo(state, seen, temp);
      return;
    }

    vector<MazeState*> nextMoves = state->getSuccessors();
    for (unsigned int i=0; i < nextMoves.size(); i++) {
      if (!seen.find(nextMoves[i], temp)) {
        // Never seen this state before.  Add it to 'seen' and 'active'
        active.add(nextMoves[i]);
        seen.add(nextMoves[i], state);
      } else {
	delete nextMoves[i];
      }
    }
  }

  // Ran out of states to explore.  No solution!
  cout << "***** No Solution Exists!!! *****\n";
  return;
}

int main ()
{
  MazeState *startState;

  // 221 STUDENTS: Initialize startState with an object of the type
  // of "maze" you want solved.
  // For some mazes, you will want to pass in a parameter
  // to specify the starting position.

  // MAZE 1:
  //startState = new TextMaze(21,41, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                       XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX XX                                     X XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X XX                                   X X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X XX                                   X X XX X X X X X XXXXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X                         X XX X X X X XXX XXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X           X$            X XX X X X XXX XXXXXXXXXXXXXXXXXXXXXXXXXXX XX X X X X X X                         X XX X X XXX X X XXXXXXXXXXXXXXXXXXXXXXX X XX X X X X X X X                       X XX X XXX X X X XXXXXXXXXXXXXXXXXXXXXXXXX XX X X                                   XX XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                       X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",1,1);
// This is what the maze looks like...
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// X                                       X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X
// X                                     X X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X
// X                                   X X X
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X X X
// X                                   X X X
// X X X X X X XXXXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X                         X X
// X X X X X XXX XXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X           X$            X X
// X X X X XXX XXXXXXXXXXXXXXXXXXXXXXXXXXX X
// X X X X X X X                         X X
// X X X XXX X X XXXXXXXXXXXXXXXXXXXXXXX X X
// X X X X X X X X                       X X
// X X XXX X X X XXXXXXXXXXXXXXXXXXXXXXXXX X
// X X X                                   X
// X XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// X                                       X
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

  // MAZE 2:  This one does well with DFS.
  //startState = new TextMaze(21,41, "                $                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           ",10,20);

  // MAZE 3:  This one does poorly with DFS, well with BFS.
  //startState = new TextMaze(21,41, "                                                                                                                                                                                                                                                                                                                                                                                                                                                   $                                                                                                                                                                                                                                                                                                                                                                                                                                        ",10,20);

  //  Maze 4:  This one frustrates BestFS
  //startState = new TextMaze(21,41,"                                          XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX                                        X XXXXXXXXXX                             X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X                                        X$",10,20);


  // This is an empty Sudoku grid:
  //startState = new Sudoku("000000000000000000000000000000000000000000000000000000000000000000000000000000000");

  // This is a medium difficulty problem:
  //startState = new Sudoku("167000000050600047000300009641057000800060005000980716700008000490006050000000671");

  // And this next one is a really easy Sudoku...
  //startState = new Sudoku("927430008060000097008000402000308005400060003800201000602000300790000080500089271");


  //startState = new SliderPuzzle(3,3,"8 7 6 5 4 3 2 1 0");
  //startState = new SliderPuzzle(4,4,"15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");
  startState = new SliderPuzzle(5,5,"24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0");
  //startState = new SliderPuzzle(6,6,"35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 1 2 0");

  //startState = new SliderPuzzle(3,3,"8 7 6 5 4 3 1 2 0"); // UNSOLVABLE...


  //ArrayStack activeStates;
  //LinkedListStack activeStates;
  //UnsortedPriorityQueue activeStates;
  HeapPriorityQueue activeStates;

  // 221 STUDENTS:  Uncomment one of these to select which dictionary to use.
  LinkedListDict seenStates;
  //AVLDict seenStates;
  //LinearHashDict seenStates;
  //DoubleHashDict seenStates;

  solveMaze(startState, activeStates, seenStates);

  // No need to delete startState or anything else, because the
  // destructor for seenStates will delete all the generated
  // MazeStates exactly once.
  // delete startState;

  return 0;
}
