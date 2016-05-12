#include "Hashtable.h"
#include <cstdlib>
#include <iostream>
#include <cassert> 

using namespace std; 

Hashtable::Hashtable(int size) {
	//constructor
	int prime = nextPrime( size ); 
	_size = size;
	if (prime != size) { 
	  cout << "Warning: size = " << size << " is not a prime number." << endl; 
/* uncomment these if you want */ 
//	  cout << "Using " << prime << " instead." << endl; 
//	  _size = prime; 
	}
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	_table = new int [ _size ];
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}
void Hashtable::clear(void) {
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}    
    

Hashtable::~Hashtable() {
	//deconstructor
	delete[] _table;
}

void Hashtable::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	_totalProbes += p;
	_numInserts += 1;
}

void Hashtable::printStats() {
	cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			_totalProbes << "/" << _numInserts;
	cout <<", size = "<< _size;
	cout <<", failures = " << _numFailures << endl;
}

float Hashtable::probeRate() {
	return (float)_totalProbes / (float)_numInserts;
}

int Hashtable::hash(int k) {
	return k % _size;
}

void Hashtable::qinsert(int k) {
	int original = k % _size; 
	int inc_amount = 0; 
	int check_post = original;
	int num_loops = 0; 

	while((_table[check_post] != EMPTY) && ( num_loops < _size) ){
		num_loops ++ ; 
		inc_amount++;
		check_post = original + (inc_amount^2);
		if(check_post > _size){
			check_post = check_post % _size; 
		}
	}

	if(num_loops < _size){
	_table[check_post] = k ; 
	tallyProbes(inc_amount);} else {
    _numFailures += 1; 
    cout << "Warning: qinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}}

void Hashtable::linsert(int k) {
	int check_post = k % _size; 
	int num_loops= 0; 

	while((_table[check_post]!= EMPTY) && (num_loops < _size)) {
		num_loops++; 
		check_post ++; 
		if(check_post > _size){
			check_post = 0 ; 
		}
	}
	if(num_loops < _size){
	_table[check_post] = k;
	num_loops++;
	tallyProbes(num_loops);
    _numFailures += 1; 
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}}

void Hashtable::dinsert(int k) {

	int hash1 = k% _size; 
	int hash2 = 13 - (k % 13); 
	int counter = 0; 
	int check_post = hash1 ; 

	while(_table[check_post]!= EMPTY) {
		counter ++; 
		check_post = hash1 + counter * hash2; 
		if(check_post > _size){
			check_post = check_post - _size; 
		}
	}
	if(counter < _size){
	_table[check_post] = k;
	counter++;
	tallyProbes(counter);
 	}else {
	_table[check_post] = k;
    _numFailures += 1; 
    cout << "Warning: dinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}}

void Hashtable::print() {
	// Print the content of the hash table.

	for (int i=0; i<_size; i++) {
		cout<<"["<<i<<"] ";
		if (_table[i] != EMPTY)
			cout << _table[i];
		cout << endl;
	}
}

bool Hashtable::checkValue(int k, int i) {
	// Check if value k is at index i. Use this to help you with testing.

	return (_table[i] == k);
}

int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if (n == 2) return true;
    if (n % 2 == 0) return false;  
    return isPrime( n, 3 ); 
}
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    return isPrime( n, divisor + 2 ); 
}

