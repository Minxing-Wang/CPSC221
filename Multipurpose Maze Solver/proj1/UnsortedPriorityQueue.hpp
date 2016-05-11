//UnsortedPriorityQueue.hpp
#ifndef _UNSORTEDPRIORITYQUEUE_HPP
#define _UNSORTEDPRIORITYQUEUE_HPP

#include <vector>
#include "BagOfMazeStates.hpp"

// A naive implementation of a priority queue, using a vector and
// searching for the max for each remove operation
//
class UnsortedPriorityQueue : public BagOfMazeStates
  {
  public:
    UnsortedPriorityQueue();
    MazeState *remove();
    void add(MazeState *element);
    bool is_empty();
    ~UnsortedPriorityQueue();

  private:
    vector<MazeState *> list;
  };

#endif

