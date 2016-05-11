#ifndef _MAZESTATE_HPP
#define _MAZESTATE_HPP

#include <iostream>
#include <vector>
using namespace std;

/*
  MazeState.hpp
  Defines the abstract class MazeState.

  This objects of this class store all the information to specify
  being in a particular point in a particular maze.

*/

class MazeState {
 public:
  // virtual destructor, since we have virtual methods
  virtual ~MazeState() { }

  // returns true if this MazeState has found a goal for the maze
  virtual bool isSolution() = 0;

  // returns a vector of possible next moves from the current MazeState.
  virtual vector<MazeState *> getSuccessors(void) = 0;

  // If you want to use BestFS, you must assign a priority value to
  // all MazeStates.  (If you don't want to use BestFS, you
  // can just return a constant for all MazeStates.)
  //
  // returns a nonnegative integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.
  virtual int getBadness(void) = 0;

  // For many dictionary implementations, it's convenient to have
  // a unique ID for each state (so we can sort them, compare them,
  // hash them, etc.)
  //
  // Returns a unique identifier for any state
  virtual string getUniqId(void) = 0;

  // print the maze state
  virtual void print (ostream& out) = 0;

  // For many purposes (e.g., a Dictionary ADT as a BST), it's
  // convenient to have a total order on MazeStates.
  // These declarations give comparison operations for this order.
  // Note that we cannot use getBadness as this order, because there
  // can be many states with the same badness.
  friend bool operator<=(MazeState &a, MazeState &b);
};

#endif
