#include <iostream>
#include <fstream> //Για ανάγνωση/εγγραφή από και προς αρχεία
#include <string>  //Για ευκολότερη διαχείριση συμβολοσειρών
#include <chrono>  //Για καταμέτρηση του χρόνου που χρειάζεται για την κατασκευή
                   //των δομών και την αναζήτηση σε αυτές
#include <stdlib.h>//Για την rand() και την srand()
#include <time.h>  //Για την time()
using namespace std;
using namespace chrono;
#include "Pair.h" //Βιβλιοθήκη για τα ζεύγη λέξεων

//Include των υλοποιημένων δομών
#include "NonSortedArray.h"   //Μη ταξινομημένος πίνακας
#include "SortedArray.h"      //Ταξινομημένος πίνακας
#include "BinarySearchTree.h" //Δυαδικό δέντρο αναζήτησης
#include "AVLTree.h"          //AVL ΔΔΑ
#include "HashTable.h"        //Πίνακας Κατακερματισμού


//Βοηθητική συνάρτηση για τη δημιουργία μιας δομής δεδομένων
template <class T>
void createStructure(T *structure, fstream &tempf, ofstream &fout) {
  //Μεταβλητές για τη χρονομέτρηση
  high_resolution_clock::time_point beginning, end;
  duration<double> duration;
  
  string a, b; //Δύο προσωρινές συμβολοσειρές

  //Καταγραφή του χρόνου που ξεκίνησε η δημιουργία της δομής
  beginning = high_resolution_clock::now();
  
  //Για κάθε ένα από τα ζεύγη, εισαγωγή στη δομή:
  tempf.clear(); //Εκκαθάριση των σφαλμάτων για να μπορεί να λειτουργήσει σωστά η seekg
  tempf.seekg(ios::beg); //Μετακίνηση στην αρχή του αρχείου
  while (tempf >> a >> b)
    structure->insert(a, b);
  
  //Καταγραφή του χρόνου που σταμάτησε η δημιουργία της δομής
  end = high_resolution_clock::now();
  
  //Υπολογισμός της διαφοράς
  duration = duration_cast<::duration<double>>(end - beginning);
  fout << "Time to create: " << duration.count() << " seconds" << endl;
}

//Βοηθητική συνάρτηση για την αναζήτηση σε μια δομή δεδομένων
template <class T>
void searchStructure(T *structure, fstream &testf, ofstream &fout) {
  //Μεταβλητές για τη χρονομέτρηση
  high_resolution_clock::time_point beginning, end;
  duration<double> duration;
  
  string a, b; //Δύο προσωρινές συμβολοσειρές

  //Καταγραφή του χρόνου που ξεκίνησε η δημιουργία της δομής
  beginning = high_resolution_clock::now();

  //Αναζήτηση κάθε ζεύγους στη δομή
  testf.clear(); //Εκκαθάριση των σφαλμάτων για να μπορεί να λειτουργήσει σωστά η seekg
  testf.seekg(ios::beg); //Μετακίνηση στην αρχή του αρχείου
  fout << endl << "Search Results: " << endl;
  Pair temp;
  while (testf >> a >> b) {
    temp = structure->search(a, b);
    fout << temp.a << ',' << temp.b << ' ' << temp.appearancecount << endl;
  }
  
  //Καταγραφή του χρόνου που σταμάτησε η δημιουργία της δομής
  end = high_resolution_clock::now();
  
  //Υπολογισμός της διαφοράς
  duration = duration_cast<::duration<double>>(end - beginning);
  fout << "Time to search: " << duration.count() << " seconds" << endl;
}


int main() {
  /***********************************************************
  *                     Δήλωση μεταβλητών                    *
  ************************************************************/
  
  string a, b, templine; //Τα strings είναι αρχικά κενά
  char temp;
  bool endofword = false, atleastoneletter = false;
  unsigned long int paircount = 0;

  srand(time(NULL)); //Αρχικοποίηση της rand()
  unsigned short int rand_value; //Για αποθήκευση μιας τυχαίας τιμής από 1 έως 1000
                                 //που θα παράγεται από τη rand()

  
  /***********************************************************
  *               Άνοιγμα των αρχείων κειμένου               *
  ************************************************************/
  
  //Δείκτες σε αρχεία κειμένου
  ifstream fin;
  ofstream fout;
  fstream tempf, testf;
  
  //Άνοιγμα του αρχείου εισόδου και έλεγχος αν το άνοιγμα έγινε σωστά
  //(έξοδος σε διαφορετική περίπτωση)
  fin.open("input.txt");
  if (!fin.is_open()) {
    cout << "Could not open input.txt file! Exiting..." << endl;
    return 0;
  }

  //Δημιουργία/εκκαθάριση του αρχείου εξόδου
  fout.open("output.txt", ios::trunc);
  if (!fout.is_open()) {
    cout << "Could not create/open output.txt! Exiting..." << endl;
    return 0;
  }

  //Δημιουργία/άνοιγμα του αρχείου temp.tsv για εγγραφή και ανάγνωση,
  //όπου τα ζεύγη συνεχόμενων λέξεων θα βρίσκονται αποθηκευμένα σε μορφή
  //"λέξηa<tab>λέξηb" (tab-separated values)
  tempf.open("temp.tsv", ios::in|ios::out|ios::trunc);
  if (!tempf.is_open()) {
    cout << "Could not create/open temp.tsv! Exiting..." << endl;
    return 0;
  }

  //Δημιουργία/άνοιγμα του αρχείου test.tsv για εγγραφή και ανάγνωση,
  //όπου θα αποθηκευτούν τα 1000 ζεύγη λέξεων με τα οποία θα γίνουν αναζητήσεις
  testf.open("test.tsv", ios::in|ios::out|ios::trunc);
  if (!tempf.is_open()) {
    cout << "Could not create/open test.tsv! Exiting..." << endl;
    return 0;
  }

  
  /***********************************************************
  *  Διάβασμα του αρχείου και δημιουργία προσωρινού αρχείου  *
  ************************************************************/
  
  //Διάβασμα της πρώτης λέξης εκτός της επανάληψης
  //(τοποθετείται στη συμβολοσειρά a)
  while (!atleastoneletter) {
    endofword = false;
    while (!endofword) {
      if (fin.get(temp)) {
        if (temp >= 'a' && temp <= 'z') {
          a += temp;
          atleastoneletter = true;
        }
        else if (temp >= 'A' && temp <= 'Z') {
          a += temp - ('A' - 'a'); //('A' - 'a' η διαφορά κεφαλαίου με πεζού λατινικού γράμματος)
          atleastoneletter = true;
        }
        else
          endofword = true;
      }
      else
        endofword = true;
    }
  }

  //Διάβασμα των υπόλοιπων λέξεων μέχρι το τέλος του αρχείου
  //(διαχωριστικό θεωρείται οποιοσδήποτε χαρακτήρας εκτός από κεφαλαίο ή πεζό λατινικό γράμμα)
  while (!fin.eof()) {
    endofword = false;
    atleastoneletter = false;

    while (!endofword) {
      if (fin.get(temp)) {
        if (temp >= 'a' && temp <= 'z') {
          b += temp;
          atleastoneletter = true;
        }
        else if (temp >= 'A' && temp <= 'Z') {
          b += temp - ('A' - 'a'); //('A' - 'a' η διαφορά κεφαλαίου με πεζού λατινικού γράμματος)
          atleastoneletter = true;
        }
        else
          endofword = true;
      }
      else
        endofword = true;
    }

    //Αν σχηματίστηκε λέξη στη συμβολοσειρά b σε αυτή την επανάληψη,
    //προσθήκη του ζεύγους λέξεων στο αρχείο temp.tsv και αντιγραφή της b στην a
    if (atleastoneletter) {
      tempf << a << '\t' << b << endl;
      paircount++;
      a = b;
    }
    b = "";
  }
  
  
  /***********************************************************
  *      Δημιουργία αρχείου με τα ζεύγη για τις δοκιμές      *
  ************************************************************/
  
  //Επιλογή 1000 τυχαίων ζευγών και προσθήκη τους στο αρχείο
  for (int i = 0; i < 1000; i++) {
    rand_value = rand() % paircount;
    tempf.clear(); //Εκκαθάριση των σφαλμάτων για να μπορεί να λειτουργήσει σωστά η seekg
    tempf.seekg(ios::beg);
    
    for (int j = 0; j < rand_value; j++)
      getline(tempf, templine);
    //Προσθήκη της γραμμής που επιλέχθηκε τυχαία στο αρχείο
    testf << templine << endl;
  }

  
  /***********************************************************
  *              Δημιουργία και δοκιμή των δομών             *
  ************************************************************/
  
  /*****************Μη ταξινομημένος πίνακας******************/
  
  //Δημιουργία του Μη ταξινομημένου πίνακα:
  NonSortedArray *arr = new NonSortedArray;
  fout << "Non-Sorted Array:" << endl;

  //Εκτέλεση των βοηθητικών συναρτήσεων για την εισαγωγή των στοιχείων
  //και την αναζήτηση
  createStructure(arr, tempf, fout);
  searchStructure(arr, testf, fout);

  //Διαγραφή της δομής
  delete arr;
  fout << endl;

  /*******************Tαξινομημένος πίνακας*******************/
  //Δημιουργία του ταξινομημένου πίνακα
  SortedArray *sarr = new SortedArray;
  fout << "Sorted Array:" << endl;

  //Εκτέλεση των βοηθητικών συναρτήσεων για την εισαγωγή των στοιχείων
  //και την αναζήτηση
  createStructure(sarr, tempf, fout);
  searchStructure(sarr, testf, fout);

  //Διαγραφή της δομής
  delete sarr;
  fout << endl;

  /*****************Δυαδικό Δέντρο Αναζήτησης*****************/

  //Δημιουργία του Δυαδικού Δέντρου Αναζήτησης
  BinarySearchTree *bst = new BinarySearchTree;
  fout << "Binary Search Tree:" << endl;

  //Εκτέλεση των βοηθητικών συναρτήσεων για την εισαγωγή των στοιχείων
  //και την αναζήτηση
  createStructure(bst, tempf, fout);
  searchStructure(bst, testf, fout);

  //Διαγραφή της δομής
  delete bst;
  fout << endl;

  /****************Δυαδικό Δέντρο Αναζήτησης AVL***************/

  //Δημιουργία του Δυαδικού Δέντρου Αναζήτησης AVL
  AVLTree *avl = new AVLTree;
  fout << "Binary AVL Search Tree:" << endl;

  //Εκτέλεση των βοηθητικών συναρτήσεων για την εισαγωγή των στοιχείων
  //και την αναζήτηση
  createStructure(avl, tempf, fout);
  searchStructure(avl, testf, fout);

  //Διαγραφή της δομής
  delete avl;
  fout << endl;

  /*************************Hash Table*************************/

  //Δημιουργία του Πίνακα Κατακερματισμού
  HashTable *ht = new HashTable;
  fout << "Hash Table:" << endl;

  //Εκτέλεση των βοηθητικών συναρτήσεων για την εισαγωγή των στοιχείων
  //και την αναζήτηση
  createStructure(ht, tempf, fout);
  searchStructure(ht, testf, fout);

  //Διαγραφή της δομής
  delete ht;
  fout << endl;
  
  /***************************Τέλος***************************/
  //Κλείσιμο των αρχείων
  fin.close();
  fout.close();
  tempf.close();
  testf.close();
}