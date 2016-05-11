//LinkedListDict.hpp
#ifndef _LINKEDLISTDICT_HPP
#define _LINKEDLISTDICT_HPP

#include "PredDict.hpp"

// An implementation of a dictionary ADT as an unsorted linked list.
// This will be very slow.
//
class LinkedListDict : public PredDict
  {
  public:
    LinkedListDict();
    ~LinkedListDict();
    bool find(MazeState *key, MazeState *&pred);
    void add(MazeState *key, MazeState *pred);

  private:
    struct node {
      MazeState *key;
      MazeState *data;
      node *next;
    };

    node *root;
  };

#endif

