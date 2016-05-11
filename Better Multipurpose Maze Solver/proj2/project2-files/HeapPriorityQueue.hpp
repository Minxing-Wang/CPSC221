//HeapPriorityQueue.hpp
#ifndef _HEAPPRIORITYQUEUE_HPP
#define _HEAPPRIORITYQUEUE_HPP

// Heap-based priority queue implemented using C++ std heap operations
#include <vector>

#include "BagOfMazeStates.hpp"

// An implementation of a priority queue, using
// a min-heap as the underlying data structure.
//
// The priority should be based on each MazeState's getBadness() value.

class HeapPriorityQueue : public BagOfMazeStates
  {
  public:
    HeapPriorityQueue();
    MazeState *remove();
    void add(MazeState *element);
    bool is_empty();
    ~HeapPriorityQueue();
    
  private:
    // The array representation of the heap.
    vector<MazeState *> heap;
  };

#endif
