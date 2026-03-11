#include "NonSortedArray.h"

#include <iostream>
#include <string>
#include "Pair.h"
using namespace std;

NonSortedArray::NonSortedArray() {
  array = new Pair[1000000]; //Δέσμευση 1000000 θέσεων στη μνήμη
  size = 0;
  maxsize = 1000000;
}

NonSortedArray::~NonSortedArray() {
  delete[] array;
}

Pair NonSortedArray::search(const string a, const string b) {
  return *searchInArray(a, b);
}

Pair *NonSortedArray::searchInArray(const string a, const string b) {
  Pair key(a, b);
  for (unsigned long long int i = 0; i < size; i++) {
    if (array[i] == key)
      return &array[i]; //Επιστροφή pointer του στοιχείου του array που ταιριάζει
  }
  return nullptr;          //Αλλιώς επιστρέφει NULL
}

void NonSortedArray::insert(const string a, const string b) {
  //Αρχικά αναζήτηση αν το στοιχείο υπάρχει ήδη,
  //και αν ναι, τότε απλά αύξηση του appearancecount κατά 1
  Pair *searchres = searchInArray(a, b);
  if (searchres) {
    searchres->appearancecount++;
    return;
  }
  
  //Αν το πλήθος των στοιχείων που βρίσκονται στον πίνακα ήδη ισούται
  //με το μέγιστο μέγεθος, αύξηση του μεγέθους του πίνακα κατά 1000000 θέσεις
  //(επιστροφή αν αποτύχει η δέσμευση μνήμης)
  if (size == maxsize)
    if (!changeAllocation(1000000))
      return;

  //Προσθήκη του στοιχείου στο array
  array[size].a = a;
  array[size].b = b;
  size++;
}

//Βοηθητική συνάρτηση για τη δέσμευση περισσότερης μνήμης
bool NonSortedArray::changeAllocation(long int changesize) {
  //Προσπάθεια δέσμευσης περισσότερης μνήμης για το array
  //(υποστηρίζονται αρνητικές τιμές στην changesize για μείωση της δέσμευσης)
  Pair *temparray = new Pair[maxsize + changesize];
  if (temparray == NULL) {
    cout << "ERROR! Could not allocate more memory!" << endl;
    return false;
  }
  maxsize += changesize;
  
  //Αντιγραφή των στοιχείων από το παλιό array στο νέο
  for (long long int i = 0; i < size; i++)
    temparray[i] = array[i];
  
  delete[] array;   //Διαγραφή του παλιού
  array = temparray;//και αλλαγή του δείκτη array ώστε να δείχνει στο καινούριο

  return true;
}