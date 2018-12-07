#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Node * newNode(Data data, Node * parent){
  Node * node = malloc(sizeof(Node));
  node->data = data;
  node->parent = parent;
  node->left = NULL;
  node->right = NULL;
  return node;
};


Tree * newTree(){
  Tree * bst = malloc(sizeof(Tree));
  bst->root = NULL;
  bst->insert = insert;
  bst->search = search;
  bst->sort = sort;
  bst->compare = compare;
  bst->clone = clone;
  bst->removeData = removeData;
  bst->delete = delete;
  return bst;
};

Data * insert(Tree * bst, Data data){
  if(bst->root == NULL)
    bst->root = newNode(data, NULL);
  else
    insertNode(bst->root, data);
};

Node * insertNode(Node * n, Data d){
  if(d.value < n->data.value){
    if(n->left == NULL)
      n->left = newNode(d, n);
    else
      insertNode(n->left, d);
  }else if(d.value > n->data.value){
    if(n->right == NULL)
      n->right = newNode(d, n);
    else
      insertNode(n->right, d);
  }
  else return NULL;
}

void sort(Tree * bst, Data * data){
  int j = 0;
  Node * node = bst->root;
  sortArray(node, data, &j); //要传地址，作为全局变量
};

void sortArray(Node * node, Data * data, int * j){
  if(node != NULL){
    sortArray(node->left, data, j);
    data[*j] = node->data;
    (*j) += 1;
    sortArray(node->right, data, j);
  }
}

Data * search(Tree * bst, Data d){
  if(bst->root == NULL){
    return NULL;
  }
  else{
    Node * tmp = searchNode(bst->root, d);
    return &(tmp->data);
  }
};

Node * searchNode(Node * n, Data d){
  if(d.value < n->data.value){
    if(n->left == NULL)
      return NULL;
    else 
      return searchNode(n->left, d);
  }
  else if(d.value > n->data.value){
    if(n->right == NULL)
      return NULL;
    else 
      return searchNode(n->right, d);
  }
  else{
    return n;
  }
}

void removeData(Tree * t, Data d){

  Node * to_delete = searchNode(t->root,d);
  if(to_delete != NULL){
    if(to_delete->left == NULL && to_delete->right == NULL)
      removeLeaf(t, to_delete);
    else if(to_delete->left == NULL || to_delete->right == NULL){
      printf("branch\n");
      shortCircuit(t, to_delete);
    }
    else{
      printf("find it\n");
      promotion(t, to_delete);
    }
      
  }
};

void removeLeaf(Tree * t, Node * n){
  printf("hi\n");
  printf("remove %d\n",n->data.value);
  if(n->parent == NULL){
    printf("this is root\n");
    t->root = NULL;
    free(n);
    n = NULL;
    printf("done\n");
  }
  else{
    if(n->parent->left == n){
      printf("reamoveleftleaf\n");
      //free(n->parent->left);
      free(n);
      n->parent->left = NULL;
    }else{
      printf("reamoverightleaf\n");
      //free(n->parent->right);
      free(n);
      n->parent->right = NULL;
    }
  }
};

void shortCircuit(Tree * t, Node * n){
  printf("removing %d\n",n->data.value);
  if (n->parent == NULL){
    if(n->left != NULL){
      t->root = n->left;
      free(t->root->parent);
      t->root->parent = NULL;
    }
    else{
      t->root = n->right;
      printf("root updated %d\n",t->root->data.value);
      printf("n %d\n",n->data.value);
      free(t->root->parent);
      t->root->parent = NULL;
    }
    //free(n);
    //n = NULL;
    //printf("root updated %d\n",n->data.value);
    //printf("root updated %d\n",t->root->parent->data.value);
    printf("done!\n");
  }
  else{
    if(n->parent->left == n){
      if(n->left != NULL){
        printf("leftleftcase\n");
        n->parent->left = n->left;
        n->left->parent = n->parent;
      }else{
        n->parent->left = n->right;
        n->right->parent = n->parent;
      }
    }
    else{
      if(n->right != NULL){
        n->parent->right = n->right;
        n->right->parent = n->parent;
      }
      else{
        n->parent->right = n->left;
        n->left->parent = n->parent;
      }
    }
    printf("shortcurcuit\n");
    free(n);
    n = NULL; 
    printf("done!\n");
  }
  
  
};

Node * findMaxLeft(Node * n){
  printf("parent %d\n",n->parent->data.value);
  printf("fingding %d\n",n->data.value);
  if(n->right == NULL){
    
    return n;}
  else
    return findMaxLeft(n->right);
};

Node * findMinRight(Node * n){
  n = n->right;
  while(n->left != NULL){
    n = n->left;
    printf("finding %d\n",n->data.value);
  }
  return n;
};

void promotion(Tree * t, Node * n){

  Node * promote = findMinRight(n);
  printf("parent of %d is %d\n",promote->data.value, promote->parent->data.value);
  n->data = promote->data;
  
  if(promote->left == NULL && promote->right == NULL){
    printf("leaf value%d\n",promote->data.value);
    printf("leaf's parent value%d\n",promote->parent->data.value);
    removeLeaf(t, promote);
  }
  else{
    promotion(t, promote);
  }
    
}



Tree * clone(Tree * bst){
  Tree * copy = newTree();
  Node * node = bst->root;
  cloneHelper(node, copy);
  return copy;
};

void cloneHelper(Node * node, Tree * copy){
  if(node != NULL){
    copy->insert(copy, node->data);
    cloneHelper(node->left, copy);
    cloneHelper(node->right, copy);
  }
}

int compare(Tree * bst, Tree * copy){
  if (bst == NULL || copy == NULL) return 0;
  Node * node1 = bst->root;
  Node * node2 = copy->root;
  return compareHelper(node1, node2);
  
};

int compareHelper(Node * node1, Node * node2){
  if (node1 != NULL && node2 != NULL){
    printf("node1: %d, node2: %d\n", node1->data.value, node2->data.value);
    if(node1->data.value != node2->data.value) return 0;
    compareHelper(node1->left, node2->left);
    compareHelper(node1->right, node2->right);
    return 1;
  }
}


void delete(Tree * t){
  deleteHelper(t, t->root);
  free(t);
  t = NULL;
};

void deleteHelper(Tree * t, Node * n){
  if(n != NULL){
    deleteHelper(t, n->left);
    deleteHelper(t, n->right);
    removeLeaf(t, n);
  }
}



