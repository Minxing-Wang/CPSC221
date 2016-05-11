#ifndef _LINEARHASHDICT_CPP
#define _LINEARHASHDICT_CPP

//LinearHashDict.cpp
#include "LinearHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a hash table with linear probing
//

const int LinearHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

const int LinearHashDict::notprimes[] = {100, 300, 1000, 3000, 10000,
      30000, 100000, 300000, 1000000, 3000000, 10000000, 30000000,
      100000000, 300000000, 1000000000, -1};
// List of bad sizes for the hash table and this hash function...

LinearHashDict::LinearHashDict() {
  size_index = 0;
  size = primes[size_index];
  //size = notprimes[size_index];
  table = new bucket[size](); // Parentheses force initialization to 0
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

LinearHashDict::~LinearHashDict() {
  // Delete all table entries...
  for (int i=0; i<size; i++) {
    if (table[i].key!=NULL) {
      delete table[i].key;
      // Don't delete data here, to avoid double deletions.
    }
  }
  // Delete the table itself
  delete [] table;

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS-1; i++)
    cout << i << ": " << probes_stats[i] << endl;
  cout << "More: " << probes_stats[MAX_STATS-1] << endl;
  delete [] probes_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the number of probes that you needed for that call to find.
// The number of probes should be the total number of buckets that you
// look at:  e.g., on an unsuccessful call to find, you should include
// the empty bucket at the end.
void LinearHashDict::record_stats(int probes) {
  if (probes> MAX_STATS-1) probes = MAX_STATS-1;
  probes_stats[probes]++;
}



int LinearHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

void LinearHashDict::rehash() {
// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the beginning of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "*** REHASHING " << size;
#endif
// End of "DO NOT CHANGE" Block


  // TODO:  Your code goes here...

  // Keep a pointer to the old table.
  int oldsize = size;

  // Get a bigger table
  size_index++;
  size = primes[size_index];
  bucket *oldtable = table;
  table = new bucket[size]();
  number = 0;

  // Rehash all the data over
  

  for(int i = 0; i < oldsize;i++){
    if (oldtable[i].key != NULL){
      add(oldtable[i].key, oldtable[i].data);
    }
  }

  // No need to delete the data, as all copied into new table.
  delete[] oldtable;

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// And leave this at the end of the rehash() function.
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << " to " << size << " ***\n";
#endif
// End of "DO NOT CHANGE" Block
}

bool LinearHashDict::find(MazeState *key, MazeState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // TODO:  Your code goes here...
    string keyId = key-> getUniqId();
    int hashKey = hash(keyId);
    int count = 1;
  
    for (int i = 0; i < size; i++){
      if (table[(hashKey + i)% size].keyId == keyId){
          
          record_stats(count);
          pred = table[(hashKey + i)% size].data; //}
          return true;
      }
      
      if (table[(hashKey + i)% size].key == NULL){
         
          record_stats(count);
          //}
          return false;
      }
      count++;
    }
return false;
}

// You may assume that no duplicate MazeState is ever added.
void LinearHashDict::add(MazeState *key, MazeState *pred) {

  // Rehash if adding one more element pushes load factor over 3/4
  if (4*(number+1) > 3*size) rehash();

  // TODO:  Your code goes here...
  string keyId = key->getUniqId();
  int hashKey = hash(keyId);

  for (int i = 0; i < size; i++){
    if (table[(hashKey + i) % size].key == NULL){
      table[(hashKey + i)% size].key = key;
      table[(hashKey + i)% size].data = pred;
      table[(hashKey + i)% size].keyId = keyId;
      number++;
      return;
    }
  }


}

#endif
