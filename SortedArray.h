#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include "NonSortedArray.h"

class SortedArray: public NonSortedArray {
private:
  Pair *binarySearch(const string a, const string b, const long long int left, const long long int right, long long int &mid);

public:
  //Για constructor/destructor κρατάμε αυτούς της NonSortedArray
  Pair search(const string a, const string b);
  void insert(const string a, const string b);
};

#endif //SORTEDARRAY_H