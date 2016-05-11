#ifndef _TEXTMAZE_HPP
#define _TEXTMAZE_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  TextMaze.hpp

  Explores a 2D rectangular maze.
*/

class TextMaze : public MazeState {
 public:
  TextMaze(int, int, string, int, int);
    // The constructor takes the number of rows and columns in the maze,
    // then a string of length row*col showing the maze, in row-major order,
    // where a space indicates open space, $ indicates a goal, and
    // other characters indicate obstacles.
    // The last two parameters are the starting row and column.
  TextMaze(const TextMaze&); // Deep copy constructor
  ~TextMaze();

  // returns true if this MazeState has reached a goal for the maze
  bool isSolution();

  // returns a vector of possible next maze states from the current maze state.
  vector<MazeState*> getSuccessors();

  // If you want to use BestFS, you must assign a priority value to
  // all maze states.  (If you don't want to use BestFS, you
  // can just return 0 for all MazeStates.)
  //
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.
  int getBadness();

  // For many dictionary implementations, it's convenient to have
  // a unique ID for each state (so we can sort them,
  // hash them, etc.)
  //
  // Returns a unique string for any state
  string getUniqId();

  // print the maze state
  void print (ostream& out);

 private:
  const int rows; // number of rows
  const int cols; // number of columns
  char *maze; // array of size rows*cols to hold the maze
  int my_row; // current row position of explorer
  int my_col; // current col position of explorer
  int target_row; // location of a $ in the maze
  int target_col;
  void move_down(); // explore downward (increase row)
  void move_up(); // explore upward (decrease row)
  void move_right(); // explore rightward (increase col)
  void move_left(); // explore leftward (decrease col)
};

#endif
