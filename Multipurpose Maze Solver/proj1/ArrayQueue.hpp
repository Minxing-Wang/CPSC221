//ArrayQueueSOLN.hpp
#ifndef _ARRAYQUEUESOLN_HPP
#define _ARRAYQUEUESOLN_HPP

#include "BagOfMazeStates.hpp"

// This skeleton file (along with the .cpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as ArrayQueue is some subtype
// of BagOfMazeStates
class ArrayQueue: public BagOfMazeStates
{
 public:
  ArrayQueue(); // constructor
  
  // BagOfMazeStates interface
  void add(MazeState *elem);
  MazeState *remove();
  bool is_empty();

  ~ArrayQueue(); // destructor

 private:
  // A helper function that consumes a number and ensures the queue
  // has enough space for that many elements.
  void ensure_capacity(int n);

  // a pointer to the underlying array with elements of type (MazeState *)
  // use an explicit pointer, NOT MazeState *array[..] so you can resize.
  MazeState **array;

  // TODO: list additional private member variables here,
  static const int INIT_SIZE = 10000;

  // index of the head of the queue.
  int head;
  // index of first free space after tail of queue
  int tail;

  // how many elements the queue is capable of holding in the underlying array
  int capacity;
};

#endif
