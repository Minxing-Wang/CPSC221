//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>
#include <vector>

HeapPriorityQueue::HeapPriorityQueue() {
  // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}

void HeapPriorityQueue::add(MazeState *elem) {
  heap.push_back(elem);
  int last = heap.size()-1;
  percolateUp(0, last);
  return;
}

MazeState * HeapPriorityQueue::remove() {
  assert(!is_empty());
  int last = heap.size()-1;
  MazeState* temp = heap[0];
  heap[0] = heap[last];
  heap[last] = temp;
  heap.pop_back();
  percolateDown(0, last-1);
  return temp;
} 

bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

// You might find these helper functions helpful...
int HeapPriorityQueue::parent(int index) {
  return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

void HeapPriorityQueue::percolateUp(int low, int high) {
  int child = high;
  while (child > low) {
    int parent = (child - 1)/2;

    if(heap[child]->getBadness() < heap[parent]->getBadness()){
      MazeState* temp = heap[child];
      heap[child] = heap[parent];
      heap[parent] = temp;
      child = parent;
    }
    else {
      break;
    }
  }
  return;
}

void HeapPriorityQueue::percolateDown(int low, int high) {
  int parent = low;
  while((parent * 2) +1 <= high) {
    int left = (parent * 2) + 1;
    int right = left + 1;
    int swap = parent;

    if((right <= high) && (heap[swap]->getBadness() > heap[right]->getBadness())){
      swap = right;
    }
    if(heap[swap]->getBadness() > heap[left]->getBadness()){
      swap = left;
    }
    if(swap != parent){
      MazeState * tmp = heap[parent];
      heap[parent] = heap[swap];
      heap[swap] = tmp;
      parent = swap;
    } else {
        break;
    }
  }
  return;
} 

#endif
