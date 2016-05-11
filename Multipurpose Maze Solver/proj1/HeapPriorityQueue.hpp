//HeapPriorityQueue.hpp
#ifndef _HEAPPRIORITYQUEUE_HPP
#define _HEAPPRIORITYQUEUE_HPP

// For this class (but not the your queue and stack classes), you
// are allowed to use the C++ STL vector class.  This saves you from
// having to resize the array when it fills up.
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
    void percolateUp(int low, int high);
    void percolateDown(int low, int high);
    
  private:
    // TODO: add any private member variables you need
    // and any additional helper functions.
    // 
    // We suggest a member variable using the C++ STL
    // type vector<MazeState *> to hold the heap.
    // You can look at the UnsortedPriorityQueue class
    // for an example of how to use the C++ vector<T> class.

    // Heap-related helper functions.
    bool is_root(int index);
    int parent(int index);
    int first_child(int index);
    int num_children(int index);
    bool is_leaf(int index);

    // The array representation of the heap.
    vector<MazeState *> heap;
  };

#endif
