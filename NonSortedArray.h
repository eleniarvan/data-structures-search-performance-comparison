#ifndef NONSORTEDARRAY_H
#define NONSORTEDARRAY_H

#include <string>
#include "Pair.h"
using namespace std;

class NonSortedArray {
protected:
  Pair *array; //Δείκτης σε πίνακα με ζεύγη λέξεων
  unsigned long long int size, maxsize;
  bool changeAllocation(long int changesize); //Βοηθητική συνάρτηση για αλλαγή μεγέθους του array
  Pair *searchInArray(const string a, const string b);

public:
  NonSortedArray(); //Constructor
  ~NonSortedArray();//Destructor/Deleter
  void insert(const string a, const string b);
  Pair search(const string a, const string b);
};

#endif //NONSORTEDARRAY_H