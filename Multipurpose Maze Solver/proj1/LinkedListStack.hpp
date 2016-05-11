//LinkedListStack.hpp
#ifndef _LINKEDLISTSTACK_HPP
#define _LINKEDLISTSTACK_HPP

#include "BagOfMazeStates.hpp"


class LinkedListStack: public BagOfMazeStates
{
 public:
  LinkedListStack();
  void add(MazeState *elem);
  MazeState *remove();
  bool is_empty();
  virtual ~LinkedListStack();

 private:
  struct node{
    MazeState *data;
    node* next;
  };
    
  node* top;
};

#endif
