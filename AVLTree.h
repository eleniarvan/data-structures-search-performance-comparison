#ifndef AVLTREE_H
#define AVLTREE_H

#include "BinarySearchTree.h"

class AVLTree : public BinarySearchTree {
private:
  Node *InsertNode(Node *k, const string &worda, const string &wordb);

  long long int getHeight (Node *k);
  Node *L(Node *parent);
  Node *R(Node *parent);
  Node *LR(Node *parent);
  Node *RL(Node *parent);

public:
  AVLTree();
  ~AVLTree();
  void insert(const string &worda, const string &wordb);
};

#endif //AVLTREE_H