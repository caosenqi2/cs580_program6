#ifndef BST_H
#define BST_H


typedef struct Data{
  int value;
} Data;

typedef struct Node{
  Data data;
  struct Node * left;
  struct Node * right;
  struct Node * parent;
} Node;

typedef struct Tree{
  Node * root;
  Data * (*insert)(struct Tree * bst, Data data);
  Data * (*search)(struct Tree * bst, Data data);
  void (*sort)(struct Tree * bst, Data * data);
  int (*compare)(struct Tree * bst, struct Tree * copy);
  struct Tree * (*clone)(struct Tree * bst);
  void (*removeData)(struct Tree * bst, Data data);
  void (*delete)(struct Tree * bst);
} Tree;


Node * newNode(Data d, Node * parent);
Tree * newTree();
Data * insert(Tree * bst, Data data);
void insertNode(Node * n, Data d);
Data * search(Tree * bst, Data data);
Node * searchNode(Node * n, Data d);

void removeData(Tree * bst, Data data);
void removeLeaf(Tree * t, Node * n);
void shortCircuit(Tree * t, Node * n);
Node * findMaxLeft(Node * n);
Node * findMinRight(Node * n);
void promotion(Tree * t, Node * n);

Tree * clone(Tree * bst);
void cloneHelper(Node *node, Tree * copy);
int compare(Tree * bst, Tree*);
int compareHelper(Node * node1, Node * node2);
void sort(Tree * bst, Data * data);
void sortArray(Node * bst, Data * data, int * j);
void delete(Tree * bst);
void deleteHelper(Tree * t, Node * n);


#endif