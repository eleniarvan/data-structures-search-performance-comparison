#include "SortedArray.h"

Pair SortedArray::search(const string a, const string b) {
  long long int pos;
  return *binarySearch(a, b, 0, size - 1, pos); //Η binarySearch είναι αναδρομική
}

Pair *SortedArray::binarySearch(const string a, const string b, const long long int left, const long long int right, long long int &pos) {
  //Υλοποίηση binary search
  Pair temp(a, b);
  pos = left;
  
  if (left <= right) {
    long long int mid = left + (right - left) / 2;
    if (array[mid] == temp)
      return &array[mid];
    if (array[mid] > temp)
      return binarySearch(a, b, left, mid - 1, pos);
    else
      return binarySearch(a, b, mid + 1, right, pos);
  }
  return nullptr;
}

void SortedArray::insert(const string a, const string b) {
  long long int pos = 0;
  
  //Αρχικά έλεγχος για το αν το ζεύγος λέξεων υπάρχει ήδη στο array
  //και αν ναι απλά αύξηση του counter
  Pair *searchres = binarySearch(a, b, 0, size - 1, pos);
  
  if (searchres) {
    searchres->appearancecount++;
    return;
  }

  //Διαφορετικά, τοποθέτηση του στοιχείου στην κατάλληλη θέση με βάση το pos
  //που είναι το τελευταίο left της binarySearch
  if (pos < 0)
    pos = 0;
  
  //Αν το πλήθος των στοιχείων που βρίσκονται στον πίνακα ήδη ισούται
  //με το μέγιστο μέγεθος, αύξηση του μεγέθους του πίνακα κατά 1000000 θέσεις
  //(επιστροφή αν αποτύχει η δέσμευση μνήμης)
  if (size == maxsize)
    if (!changeAllocation(1000000))
      return;

  //Μετακίνηση όλων των στοιχείων που βρίσκονται από τη θέση pos και μετά μία θέση δεξιά
  for (long long int i = size - 1; i >= pos; i--)
    array[i + 1] = array[i];
  
  array[pos].a = a;
  array[pos].b = b;
  array[pos].appearancecount = 1;
  size++;
}