#ifndef _PREDDICT_HPP
#define _PREDDICT_HPP

#include "MazeState.hpp"

// generally not good to use a specific namespace in headers,
// for re-usability reasons, but we'll make an exception for
// this project
using namespace std;

// PredDict is a base interface representing a dictionary that
// keeps track of the predecessor state of each MazeState in the
// dictionary (i.e., if we lookup a state that we've been to,
// the associated data field is the state that we came from when
// we first discovered this state.)

// We will use this both to keep track of whether we've
// explored a state before (so we don't duplicate work
// or get stuck in cycles), as well as to generate the
// sequence of states leading to a maze solution, if
// that's desired.

// Different implementations will have different efficiency.

class PredDict {
 public:
  // a destructor declared as virtual in the
  // class declaration is given an implementation
  // so that the C++ "delete" operator on a subtype
  // will propagate up the type hierarchy into the
  // parent classes
  virtual ~PredDict() { }

  // Returns true iff the key is found.
  //
  // If the key is found, pred is set to the predecessor.
  // Do not delete the object pointed to by pred, as there will
  // still be a pointer to that object inside the dictionary.
  virtual bool find(MazeState *key, MazeState *&pred) = 0;

  // add a (key, predecessor) pair to the dictionary
  //
  // Note:  Do not delete the object pointed to by key or pred,
  //        since the dictionary will keep a link to the object.
  virtual void add(MazeState *key, MazeState *pred) = 0;
};

#endif
