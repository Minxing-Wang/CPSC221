#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

#include "MazeState.hpp"
#include "SliderPuzzle.hpp"

SliderPuzzle::SliderPuzzle(int r, int c, string config) : rows(r), cols(c) {
  int i, j;

  // I assume that the string 'config' is a list of unique integers
  // from 0 to rows*cols-1, which are filled into the board in
  // row-major order.  The 0 indicates the empty space.
  stringstream config_stream;
  config_stream << config;
  board = new int[rows*cols];
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      config_stream >> board[i*cols+j];
    }
  }
  // Now, find the location of the empty space.
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      if (board[i*cols+j]==0) {empty_row=i; empty_col=j;}
    }
  }
  uniqId = ""; // Not computed yet.
  badness = -1; // Not computed yet.
}

SliderPuzzle::SliderPuzzle(const SliderPuzzle& other) : rows(other.rows), cols(other.cols) {
  board = new int[rows*cols];
  for (int i=0; i<rows*cols; i++) {
    board[i] = other.board[i];
  }
  empty_row = other.empty_row;
  empty_col = other.empty_col;
  uniqId = other.uniqId;
  badness = other.badness;
}

SliderPuzzle::~SliderPuzzle() { delete [] board; }

bool SliderPuzzle::isSolution() {
  // We've solved it if all numbers are in order, except for the
  // empty space at the end.
  for (int i=1; i < rows*cols; i++) {
    if (board[i-1]!=i) return false;
  }
  if (board[rows*cols-1]!=0) return false;
  return true;
}



void SliderPuzzle::slide_down() {
  // Slide the tile from above into the empty spot.
  board[empty_row*cols+empty_col] = board[(empty_row-1)*cols+empty_col];
  empty_row--;
  // Make that spot the empty one.
  board[empty_row*cols+empty_col] = 0;
  uniqId = ""; // Modified state, must recompute
  badness = -1; // Modified state, must recompute
}

void SliderPuzzle::slide_up() {
  // Slide the tile from below into the empty spot.
  board[empty_row*cols+empty_col] = board[(empty_row+1)*cols+empty_col];
  empty_row++;
  // Make that spot the empty one.
  board[empty_row*cols+empty_col] = 0;
  uniqId = ""; // Modified state, must recompute
  badness = -1; // Modified state, must recompute
}

void SliderPuzzle::slide_right() {
  // Slide the tile from the left into the empty spot.
  board[empty_row*cols+empty_col] = board[empty_row*cols+empty_col-1];
  empty_col--;
  // Make that spot the empty one.
  board[empty_row*cols+empty_col] = 0;
  uniqId = ""; // Modified state, must recompute
  badness = -1; // Modified state, must recompute
}

void SliderPuzzle::slide_left() {
  // Slide the tile from the right into the empty spot.
  board[empty_row*cols+empty_col] = board[empty_row*cols+empty_col+1];
  empty_col++;
  // Make that spot the empty one.
  board[empty_row*cols+empty_col] = 0;
  uniqId = ""; // Modified state, must recompute
  badness = -1; // Modified state, must recompute
}


vector<MazeState*> SliderPuzzle::getSuccessors() {

  vector<MazeState*> result;

  // Can I move the empty space up?
  if (empty_row!=0) {
    SliderPuzzle* temp = new SliderPuzzle(*this);
    temp->slide_down();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move the empty space down?
  if (empty_row!=rows-1) {
    SliderPuzzle* temp = new SliderPuzzle(*this);
    temp->slide_up();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move the empty space left?
  if (empty_col!=0) {
    SliderPuzzle* temp = new SliderPuzzle(*this);
    temp->slide_right();
    // Add it to the results
    result.push_back(temp);
  }
  // Can I move the empty space right?
  if (empty_col!=cols-1) {
    SliderPuzzle* temp = new SliderPuzzle(*this);
    temp->slide_left();
    // Add it to the results
    result.push_back(temp);
  }

  return result;
}

int SliderPuzzle::getBadness() {
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.

  // Check if we've computed badness previously...
  if (badness != -1) return badness;

  // For each tile, we'll add up how far it is from where it should be.
  int cost=0;
  for (int i=0; i < rows; i++) {
    for (int j=0; j < cols; j++) {
      int tile = board[i*cols+j];
      if (tile!=0) {
        int target_row = (tile-1)/cols;
        int target_col = (tile-1)%cols;
	cost += abs(i-target_row) + abs(j-target_col);
      }
    }
  }
  badness = cost; // memoize computed badness for future reference
  return cost;
}

string SliderPuzzle::getUniqId() {
  // Check if we've computed unique ID already
  if (uniqId != "") return uniqId;

  // This is a bit of a kludge, but it's easy.
  // We'll just use the print method to convert the MazeState
  // into a string representation.
  ostringstream temp;
  print(temp);
  uniqId = temp.str(); // memomize computed uniqID for future reference
  return uniqId;
}

void SliderPuzzle::print (ostream& out) {
  for (int i=0; i<rows; i++) {
    for (int j=0; j<cols; j++) {
      out << "\t" << board[i*cols+j];
    }
    out << endl;
  }
}
