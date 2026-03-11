#include "BinarySearchTree.h"

#include <string>
#include "Pair.h"
using namespace std;

//Constructor
BinarySearchTree::BinarySearchTree() {}

//Destructor
//(καλεί τη DeleteNode για τη ρίζα του δέντρου, με αποτέλεσμα να διαγραφεί όλο το δέντρο)
BinarySearchTree::~BinarySearchTree() {root = DeleteNode(root);}


//Εισαγωγή κόμβου
void BinarySearchTree::insert(const string &worda, const string &wordb) {
  root = InsertNode(root, worda, wordb);
}

//Εισαγωγή ενός νέου ζεύγους λέξεων στο δέντρο με αναδρομικό τρόπο
//(αν υπάρχει ήδη απλά αυξάνεται η μεταβλητή appearancecount)
Node *BinarySearchTree::InsertNode(Node *k, const string &worda, const string &wordb) {
  if (!k) { //Εαν ο δείκτης δείχνει σε κενό κόμβο, δεσμεύεται μνήμη για τον νέο κόμβο
    k = new Node(worda, wordb);
    return k;
  }
  
  //Διαφορετικά, εύρεση της θέσης στην οποία πρέπει να τοποθετηθεί ο νέος κόμβος
  Pair temp(worda, wordb); //Προσωρινό ζεύγος για συγκρίσεις

  if (temp == k->pair) { //Aν ο τρέχον κόμβος περιέχει το ζεύγος λέξεων που ψάχνουμε, τότε αύξηση του μετρητή
    k->pair.appearancecount++;
    return k;
  }
  
  if (temp < k->pair) { //Εαν το ζεύγος είναι μικρότερο απο το ζεύγος που περιέχεται στον τρέχον κόμβο
    k->leftChild = InsertNode(k->leftChild, worda, wordb); //εισάγουμε στο αριστερό παιδί του κόμβου
    return k;
  }
  
  k->rightChild = InsertNode(k->rightChild, worda, wordb); //Αλλιώς εισάγουμε στο δεξί παιδί του κόμβου
  return k;
}


//Αναζήτηση κόμβου
Pair BinarySearchTree::search(const string &worda, const string &wordb) {
  return SearchNode(root, worda, wordb)->pair;
}

//Αναδρομική υλοποίηση της αναζήτησης σε ΔΔΑ
Node *BinarySearchTree::SearchNode(Node *k, const string &worda, const string &wordb) {
  if (!k)           //Σε περίπτωση που ο κόμβος έναρξης που δόθηκε ως όρισμα δεν υπάρχει,
    return nullptr; //έξοδος με επιστροφή δείκτη στο κενό

  Pair temp(worda, wordb); //Δημιουργία προσωρινού κόμβου που θα χρησιμοποιηθεί 
                               //για τις συγκρίσεις εντός της συνάρτησης

  if (temp == k->pair)
    return k; //Σε περίπτωση που ο τρέχον κόμβος έχει το ζητούμενο ζεύγος λέξεων, επιστροφή της διεύθυνσής του

  if (temp < k->pair) //Αν το αναζητούμενο ζεύγος είναι μικρότερο από τον τρέχον κόμβο,
    return SearchNode(k->leftChild, worda, wordb); //αναδρομική αναζήτηση για το αριστερό του υπόδεντρο
  
  return SearchNode(k->rightChild, worda, wordb); //Αλλιώς, αναδρομική αναζήτηση για το δεξί του υπόδεντρο
}


//Διαγραφή του κόμβου που δίνεται ως όρισμα καθώς και όλων των παιδιών του (χρησιμοποιείται μόνο για διαγραφή όλου του δέντρου στο τέλος)
Node *BinarySearchTree::DeleteNode(Node *k) {
  if (!k)     //Σε περίπτωση που δεν υπάρχει ο κόμβος
    return nullptr; //τότε απλά έξοδος από τη συνάρτηση επιστρέφοντας δείκτη NULL

  //Αναδρομική εκτέλεση της DeleteNode για το αριστερό και το δεξί παιδί του κόμβου (αν υπάρχουν)
  if (k->leftChild)
    k->leftChild = DeleteNode(k->leftChild);
  if (k->rightChild)
    k->rightChild = DeleteNode(k->rightChild);

  //Στο τέλος, διαγραφή του ίδιου του κόμβου και θέση του pointer που περάστηκε στη συνάρτηση σε NULL
  //ώστε ο γονικός κόμβος να μη δείχνει πλέον σε αυτόν
  delete k;
  k = nullptr;
  
  return k;
}