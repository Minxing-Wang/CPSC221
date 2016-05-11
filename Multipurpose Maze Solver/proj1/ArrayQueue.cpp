#ifndef _ARRAYQUEUESOLN_CPP
#define _ARRAYQUEUESOLN_CPP

//ArrayQueueSoln.cpp

#include "ArrayQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
using namespace std;

// 221 STUDENTS:
//
// This skeleton file (along with the .hpp) is
// here to help get you started, but you are
// free to change function signatures, etc.
// as long as ArrayQueue is some subtype
// of BagOfMazeStates
ArrayQueue::ArrayQueue()
{
  // Constructor: initialize member variables
  //              and do any other initialization
  //              needed (if any)
  array = new MazeState*[INIT_SIZE];
  capacity = INIT_SIZE;
  head = tail = -1;
}

void ArrayQueue::add(MazeState *elem)
{
  // TODO: implement add method
  if ((tail+1) % capacity == head) {
    ensure_capacity(capacity+1); 
  }
  tail = (tail + 1) % capacity;
  array[tail] = elem;
  if(head == -1)
    head = 0;
}

MazeState *ArrayQueue::remove()
{
  // TODO: implement remove method
  assert(!is_empty());
  MazeState *temp = array[head];
  if(head == tail){
    head = tail = 0;
  }else {
   head = (head+1) % (capacity);
 }
 return temp;
}

bool ArrayQueue::is_empty()
{
  // TODO: implement is_empty method
  return (head == -1);
}

// TODO: implement ensure_capacity (but leave this to last.. just start with lots of capacity!)
void ArrayQueue::ensure_capacity(int n)
{
  if (capacity < n) {
    // Make plenty of room.
    int target_capacity = (n > 2*capacity+1) ? n : (2*capacity+1);

    // TODO: Set the current array aside and make room for the new one.
    MazeState **old_array = array;
    array = new MazeState* [target_capacity];

    // TODO: Copy each element of the old array over.
    // Update front carefully as you go!  Can you just use front++?
    for(int i=0; i<capacity; i++){
      array[i] = old_array[head];
      head = (head + 1) % capacity;
    }
      head = 0;
      tail = capacity - 1;
      capacity = target_capacity;
    // TODO: Fix front and back and capacity so they correspond to the new array.
    // TODO: Delete the old array.
    delete [] old_array;
  }
}


ArrayQueue::~ArrayQueue()
{
  delete [] array;
}

#endif
