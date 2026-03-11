#ifndef PAIR_H
#define PAIR_H

#include <string>
using namespace std;

class Pair {
public:
  string a, b;
  int appearancecount = 1;

  Pair() {}
  Pair(const string a, const string b) {this->a = a; this->b = b;}

  //Operator overloads για τη σύγκριση
  //Για τη σύγκριση δύο ζευγών λαμβάνεται υπόψη πρώτα η πρώτη λέξη, και, αν είναι ίδια, τότε ελέγχεται η δεύτερη
  bool operator== (Pair &ob) {return a == ob.a && b == ob.b;}

  bool operator< (Pair &ob) {
    if (a < ob.a)
      return true;
    if (a > ob.a)
      return false;
    return b < ob.b;
  }

  bool operator> (Pair &ob) {
    if (a > ob.a)
      return true;
    if (a < ob.a)
      return false;
    return b > ob.b;
  }
};

#endif //PAIR_H