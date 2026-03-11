#include "AVLTree.h"
#include <algorithm> //Για τη max

//Constructor
AVLTree::AVLTree(): BinarySearchTree() {}

//Destructor
AVLTree::~AVLTree() {root = DeleteNode(root);}


//Εισαγωγή νέου κόμβου στο δέντρο
void AVLTree::insert(const string &worda, const string &wordb) {
  root = InsertNode(root, worda, wordb);
}

//Εισαγωγή στο δέντρο AVL (με κατάλληλο έλεγχο για το αν παραμένει AVL και εκτέλεση περιστροφών αν δεν είναι)
Node* AVLTree::InsertNode(Node *k, const string &worda, const string &wordb) {  
  if (!k) {  //Αν ο κόμβος που δοθεί δεν υπάρχει, δημιουργία του
    k = new Node(worda, wordb);
    return k;
  }

  Pair temp(worda, wordb); //Προσωρινό ζεύγος για χρήση στις συγκρίσεις

  //Aν ο τρέχον κόμβος περιέχει το ζεύγος λέξεων που ψάχνουμε, τότε αύξηση του μετρητή και επιστροφή
  if (temp == k->pair) {
    k->pair.appearancecount++;
    return k;
  }
  
  if (temp < k->pair) //Aν το ζεύγος λέξεων που πάμε να εισάγουμε είναι μικρότερο του ζεύγους στον κόμβο k
    k->leftChild = InsertNode(k->leftChild, worda, wordb); //τότε αναδρομική εκτέλεση της συνάρτησης για το αριστερό του υπόδεντρο
  else //Αλλιώς αναδρομική εκτέλεση της συνάρτησης για το δεξί του υπόδεντρο
    k->rightChild = InsertNode(k->rightChild, worda, wordb);

  
  /**********Έλεγχος αν παραμένει AVL**********/
  long long int leftheight = getHeight(k->leftChild);
  long long int rightheight = getHeight(k->rightChild);
  
  //Ενημέρωση του ύψους του τρέχοντος κόμβου του δέντρου
  k->height = max(leftheight, rightheight) + 1;

  //Διαφορά ανάμεσα στο ύψος του αριστερού και του δεξιού για επιλογή της κατάλληλης περιστροφής
  int diff = leftheight - rightheight;

  //Αν η διαφορά μεταξύ των υψών των υποδέντρων είναι κατά απόλυτη τιμή μεγαλύτερη απο 1, τότε εκτέλεση της ανάλογης περιστροφής
  if (diff > 1) {
    if (temp < k->leftChild->pair)
      return R(k);
    else if (temp > k->leftChild->pair)
      return LR(k);
  }
  if (diff < -1) {
    if (temp < k->rightChild->pair)
      return RL(k);
    else if (temp > k->rightChild->pair)
      return L(k);
  }
  return k;
}


//Συνάρτηση που επιστρέφει το ύψος του δέντρου (αν υπάρχει ο κόμβος που δίνεται ως ρίζα)
long long int AVLTree::getHeight(Node *k) {
  if (!k)
    return 0;
  return k->height;
}


//L περιστροφή
Node *AVLTree::L(Node *k) {
  Node *temp = k->rightChild; //Δημιουργία ενός νέου προσωρινού κόμβου που θα είναι η νέα ρίζα του δέντρου
  k->rightChild = temp->leftChild; //για το οποίο καλέστηκε η L
  temp->leftChild = k;

  //ενημέρωση του ύψους των κόμβων
  k->height = max(getHeight(k->leftChild), getHeight(k->rightChild)) + 1;
  temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild)) + 1;

  return temp;
}

//R περιστροφή
Node *AVLTree::R(Node *k) {
  Node *temp = k->leftChild;
  k->leftChild = temp->rightChild;
  temp->rightChild = k;

  //ενημέρωση του ύψους τον κόμβων
  k->height = max(getHeight(k->leftChild), getHeight(k->rightChild)) + 1;
  temp->height = max(getHeight(temp->leftChild), getHeight(temp->rightChild)) + 1;

  return temp;
}

//LR περιστροφή
Node *AVLTree::LR(Node *k) {
  Node *temp = k->leftChild;
  k->leftChild = L(temp);
  return R(k);
}

//RL περιστροφή
Node *AVLTree::RL(Node *k) {
  Node *temp = k->rightChild;
  k->rightChild = R(temp);
  return L(k);
}