#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>
#include "Pair.h"
using namespace std;

//Δομή κάθε κόμβου του δέντρου
struct Node {
  Pair pair;
  long long int height = 1; //Για χρήση στο AVL Δέντρο
  Node *leftChild = nullptr, *rightChild = nullptr;

  //Κατασκευαστής που δέχεται ως παραμέτρους δύο μεταβλητές
  Node(string worda, string wordb) {pair.a = worda; pair.b = wordb;}
};

class BinarySearchTree {
private:
  Node *SearchNode(Node *k, const string &worda, const string &wordb);

protected:
  Node *root = nullptr; //Δείκτης που δείχνει στη ρίζα του δέντρου
  Node *InsertNode(Node *k, const string &worda, const string &wordb);
  Node *DeleteNode(Node *k); //Συνάρτηση που διαγράφει τον κόμβο που δίνεται ως όρισμα
                             //καθώς και όλα τα παιδιά του

public:
  BinarySearchTree();  //Constructor
  ~BinarySearchTree(); //Destructor
  void insert(const string &worda, const string &wordb);
  Pair search(const string &worda, const string &wordb);
};

#endif //BINARYSEARCHTREE_H