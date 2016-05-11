//LinkedListQueue.cpp
#ifndef _LINKEDLISTQUEUE_CPP
#define _LINKEDLISTQUEUE_CPP

#include "LinkedListQueue.hpp"
#include <cstdlib> //for NULL
#include <cassert>
#include <iostream>
LinkedListQueue::LinkedListQueue()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

void LinkedListQueue::add(MazeState *elem)
{
  node* temp = new node;

  if(is_empty()) {
  	temp->data = elem;
  	temp->next = NULL;
  	size = size+1;
  	head = temp;
  }
  else{
  	temp->data = elem;
  	temp->next = NULL;
  	tail->next = temp;
  	size = size + 1;
  }
  tail = temp;
}

MazeState *LinkedListQueue::remove()
{
  assert(!is_empty());
  MazeState *data = head->data;
  node *temp = head;

  if(!head->next) {
  	tail = NULL;
  }
  head = head->next;
  size = size - 1;
  delete temp;
  return data;
  }

bool LinkedListQueue::is_empty()
{
  return (head == NULL);
}

LinkedListQueue::~LinkedListQueue()
{
	while(head != NULL)
		remove();
}

#endif

