#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "Pair.h"
using namespace std;

class HashTable {
private:
  Pair *hashtable;
  unsigned long long int size = 0;
  unsigned long long int maxsize = 1000003;

  void doubleSize();
  bool isPrime(unsigned long long int n);
  unsigned long long int findNextPrime(unsigned long long int n);

  unsigned long long int stringsToInt(const string &worda, const string &wordb, const unsigned int P, const unsigned long M);

public:
  HashTable();
  ~HashTable();
  unsigned long long int insert(const string &worda, const string &wordb);
  Pair search(const string &word, const string &wordb);
};

#endif //HASHTABLE_H