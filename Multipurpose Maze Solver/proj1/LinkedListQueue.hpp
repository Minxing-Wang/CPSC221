//LinkedListQueue.hpp
#ifndef _LINKEDLISTQUEUE_HPP
#define _LINKEDLISTQUEUE_HPP

#include "MazeState.hpp"
#include "BagOfMazeStates.hpp"

class LinkedListQueue: public BagOfMazeStates
{
 public:
  LinkedListQueue();
  void add(MazeState *elem);
  MazeState *remove();
  bool is_empty();
  virtual ~LinkedListQueue();

 private:
  struct node{
    node* next;
    MazeState *data;
  };
    
  node* head;
  node* tail;
  int size;
};

#endif
