#include "HashTable.h"
#include <math.h>

//Σταθερές για τη συνάρτηση κατακερματισμού
#define P1 31
#define M1 1000000009
#define P2 37
#define M2 1000000007

//Constructor/Destructor
HashTable::HashTable() {hashtable = new Pair[maxsize];}
HashTable::~HashTable() {delete[] hashtable;}


//Εισαγωγή ζεύγους λέξεων στον πίνακα
unsigned long long int HashTable::insert(const string &worda, const string &wordb) {
  if (size/maxsize > 0.5) //Αν το load factor του πίνακα είναι μεγαλύτερο από 0.5
    doubleSize();         //τότε διπλασιασμός του πίνακα
  
  unsigned long long int location = stringsToInt(worda, wordb, P1, M1) % maxsize; //Αρχική θέση
  unsigned long long int h2 = stringsToInt(worda, wordb, P2, M2) % maxsize; //Βήμα
  Pair temp(worda, wordb);

  for (unsigned long long int i = 0; i <= size; i++) {
    if (hashtable[location] == temp) {       //Αν το ζεύγος λέξεων βρίσκεται ήδη στο hash table
      hashtable[location].appearancecount++; //τότε απλά αύξηση του appearancecount και έξοδος
      return location;
    }
    if (hashtable[location].a.empty()) {
      hashtable[location] = temp;
      size++;
      return location;
    }
    //Σύγκρουση (αντιμετωπίζεται με την τεχνική του διπλού κατακερματισμού)
    location = (location + h2) % maxsize;
  }
  return location;
}

//Αναζήτηση για ζεύγος λέξεων στον πίνακα
Pair HashTable::search(const string &worda, const string &wordb) {
  unsigned long long int location = stringsToInt(worda, wordb, P1, M1) % maxsize; //Αρχική θέση
  unsigned long long int h2 = stringsToInt(worda, wordb, P2, M2) % maxsize; //Βήμα
  Pair temp(worda, wordb);

  for (unsigned long long int i = 0; i <= size; i++) {
    if (hashtable[location] == temp)
      return hashtable[location];
    
    if (hashtable[location].a.empty()) {
      return Pair("", "");
    }
    
    //Σύγκρουση (αντιμετωπίζεται με την τεχνική του διπλού κατακερματισμού)
    location = (location + h2) % maxsize;
  }
  return Pair("","");
}


//Διπλασιασμός του μεγέθους του πίνακα
//για μέγεθος χρησιμοποιείται ο επόμενος πρώτος αριθμός του 2*maxsize
void HashTable::doubleSize() {
  Pair *temp = hashtable; //Διατήρηση του δείκτη του προηγούμενου πίνακα στη μεταβλητή temp
  unsigned long long int tempmaxsize = maxsize; //και του μεγέθους του στη μεταβλητή tempmaxsize
  maxsize = findNextPrime(maxsize * 2); //και δημιουργία νέου με τουλάχιστον 2πλάσιο μέγεθος
  hashtable = new Pair[maxsize];

  for (unsigned long long int i=0; i < tempmaxsize; i++) {
    if (!temp[i].a.empty()) {
      unsigned long long int loc = insert(temp[i].a, temp[i].b);
      hashtable[loc].appearancecount = temp[i].appearancecount;
    }
  }

  delete[] temp; //Διαγραφή του παλιού πίνακα
}


//Βοηθητική συνάρτηση που ελέγχει αν ένας αριθμός είναι πρώτος
bool HashTable::isPrime(unsigned long long int n) {
  if (n <= 1) //Αν ο αριθμός είναι <= 1 τότε δεν είναι πρώτος
    return false;

  unsigned long long int sqrtn = sqrt(n);
  for (unsigned long long int i = 2; i <= sqrtn; i++)
    if (n % i == 0) //Έλεγχος αν ο αριθμός διαιρείται ακριβώς με κάποιον αριθμό
      return false; //μέχρι και την τετρ. ρίζα του στην οποία περίπτωση δεν είναι πρώτος

  return true; //Σε διαφορετική περίπτωση, ο n είναι πρώτος
}

//Βοηθητική συνάρτηση που επιστρέφει τον επόμενο πρώτο αριθμό
unsigned long long int HashTable::findNextPrime(unsigned long long int n) {
  long long int i;
  bool flag = false;

  //Το i αρχικά θα πάρει την τιμή n+1, γιατί ξέρουμε ότι το n, όντας διπλάσιο του προηγούμενου μεγέθους του πίνακα, θα είναι άρτιος αριθμός και άρα όχι πρώτος.
  //Έτσι, αυξάνουμε το n κατά ένα αρχικά για να είναι περιττός αριθμός και στη συνέχεια το αυξάνουμε κατά 2 σε κάθε βήμα έτσι ώστε να μην κάνουμε περιττούς ελέγχους για τους άρτιους αριθμούς που δεν μπορούν να είναι πρώτοι.
  for (i = n + 1; !flag; i += 2)
    if (isPrime(i))
      flag = true;
  
  return i - 2;
}


//Συνάρτηση που μετατρέπει τις δύο συμβολοσειρές που της δίνονται σε έναν ακέραιο αριθμό που θα χρησιμοποιηθεί για την εύρεση της θέσης στην οποία θα πρέπει να εισαχθεί το αντικείμενο καθώς και για το βήμα που θα γίνει σε περίπτωση σύγκρουσης
unsigned long long HashTable::stringsToInt(const string &worda, const string &wordb, const unsigned int P, const unsigned long M) {
  unsigned long long hash = 0;
  unsigned long long power_of_P = 1;

  unsigned int strlena = worda.length();
  for (unsigned int i = 0; i < strlena; i++) {
    hash = hash + (worda[i] - 'a' + 1) * power_of_P;
    power_of_P = (power_of_P * P) % M;
  }

  unsigned int strlenb = wordb.length();
  for (unsigned int i = 0; i < strlenb; i++) {
    hash = hash + (wordb[i] - 'a' + 1) * power_of_P;
    power_of_P = (power_of_P * P) % M;
  }
  
  return hash;
}