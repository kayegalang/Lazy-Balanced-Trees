#ifndef LAZYBST_H
#define LAZYBST_H

#include <iostream>
using namespace std;

template <class T>
class TreeNode{
public:
  TreeNode();
  TreeNode(int k, T v);
  virtual ~TreeNode();

  int key;
  T value;
  TreeNode<T> *left;
  TreeNode<T> *right;
  int leftDepth;
  int rightDepth;
};

template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = NULL;
  value = NULL;
  leftDepth = 0;
  rightDepth = 0;
}

template <class T>
TreeNode<T>::TreeNode(int k, T v)
{
  left = NULL;
  right = NULL;
  key = k;
  value = v;
  rightDepth = 0;
  leftDepth = 0;
}

template <class T>
TreeNode<T>::~TreeNode() {
  left = NULL;
  right = NULL;
  delete left;
  delete right;
}

template <class T>
class LazyBST{
public:
  LazyBST();
  virtual ~LazyBST();
  void RecursiveDelete(TreeNode<T> *node);

  void insert(int key, T value);
  bool contains(int key); //search function
  T getValue(int key);
  bool deleteNode(int key);
  void deleteTree();
  TreeNode<T> *getSuccessor(TreeNode<T> *nodeToBeDeleted);
  void BalanceTree();
  void MoveTreeToArray(TreeNode<T>* node, int* keyArray, T* valueArray, int& index);
  void MoveArrayToTree(int* keyArray, T* valueArray, int lowerIndex, int higherIndex);

  bool isEmpty(); 
  T* getMin();
  T* getMax();

  void printTree();
  void recursivePrint(TreeNode<T> *node);
  void calculateDepths(TreeNode<T> *node);
  int calculateLeftDepth(TreeNode<T> *node);
  int calculateRightDepth(TreeNode<T> *node);
  void updateDepths(TreeNode<T> *node);

  TreeNode<T> *root;
  int size;
  
};

template <class T>
LazyBST<T>::LazyBST() {
  root = NULL;
  size = 0;
}

template <class T>
LazyBST<T>::~LazyBST() {
  RecursiveDelete(root);
}

template <class T>
void LazyBST<T>::deleteTree() {
    while (!isEmpty()) {
        deleteNode(root->key);
    }
}

template <typename T>
void LazyBST<T>::RecursiveDelete(TreeNode<T> *node){
  if(node != NULL){
    RecursiveDelete(node->left);
    RecursiveDelete(node->right);
    delete node;
  }
}

template <typename T>
void LazyBST<T>::BalanceTree() {
  int higherIndex = size;
  int* keyArray = new int[higherIndex];
  T* valueArray = new T[higherIndex];
  int index = 0;
  MoveTreeToArray(root, keyArray, valueArray, index);
  deleteTree();
  MoveArrayToTree(keyArray, valueArray, 0, higherIndex);
}

template <typename T> 
void LazyBST<T>::MoveTreeToArray(TreeNode<T>* node, int* keyArray, T* valueArray, int& index)
{
    if (node == NULL)
        return;

    // Traverse left subtree
    MoveTreeToArray(node->left, keyArray, valueArray, index);

    // Visit node and add to array
    keyArray[index] = node->key;
    valueArray[index] = node->value;
    ++index;
    // Traverse right subtree
    MoveTreeToArray(node->right, keyArray, valueArray, index);
}

template <typename T>
void LazyBST<T>::MoveArrayToTree(int* keyArray, T* valueArray, int lowerIndex, int higherIndex) {
    int median = (lowerIndex + higherIndex) / 2;
    // Insert the median value into the tree
    insert(keyArray[median], valueArray[median]);
    
  // Recursively build the left subtree with values less than the median
  if (lowerIndex < median) {
      MoveArrayToTree(keyArray, valueArray, lowerIndex, median - 1);
  }

  // Recursively build the right subtree with values greater than the median
  if (higherIndex > median) {
      MoveArrayToTree(keyArray, valueArray, median + 1, higherIndex);
  }
}


template <class T>
void LazyBST<T>::updateDepths(TreeNode<T> *node) {
  if (node == NULL) {
    return;
  }
  calculateDepths(node);
  updateDepths(node->left);
  updateDepths(node->right);
}

template <class T>
void LazyBST<T>::recursivePrint(TreeNode<T> *node) {
  if(node == NULL) {
    return;
  }
  cout << node->key << endl;
  recursivePrint(node->left);
  recursivePrint(node->right);
}

template <class T>
void LazyBST<T>::printTree(){
  recursivePrint(root);
}

template <class T>
int LazyBST<T>::calculateLeftDepth(TreeNode<T> *node) {
  if (node == NULL) {
    return 0;
  }
  else {
    int leftDepth = calculateLeftDepth(node->left);
    return ++leftDepth;
  }
}

template <class T>
int LazyBST<T>::calculateRightDepth(TreeNode<T> *node) {
  if (node == NULL) {
    return 0;
  }
  else {
    int rightDepth = calculateRightDepth(node->right);
    return ++rightDepth;
  }
}

template <class T>
void LazyBST<T>::calculateDepths(TreeNode<T> *node) {
  node->leftDepth = calculateLeftDepth(node);
  node->rightDepth = calculateRightDepth(node);
  if (abs(node->leftDepth - node->rightDepth) > 1.5) {
    BalanceTree();
  }
}

template <class T>
bool LazyBST<T>::isEmpty() {
  return root == NULL;
}

template <class T>
T* LazyBST<T>::getMin() {
  if(isEmpty()) {
    return NULL;
  }

  TreeNode<T> *current = root;
  while(current->left != NULL) {
    current = current->left;
  }

  return &current->key;
  
}

template <class T>
T* LazyBST<T>::getMax() {
  if(isEmpty()) {
    return NULL;
  }

  TreeNode<T> *current = root;
  while(current->right != NULL) {
    current = current->right;
  }

  return &current->key;

}

template <class T>
void LazyBST<T>::insert(int key, T value) {
  TreeNode<T> *node = new TreeNode<T>(key, value);

  if(isEmpty()) {
    root = node;
  }
  else { //tree was not empty
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;

    while(true) {
      parent = current;
      
      if(key < current->key) {
        //go left
        current = current->left;
        if(current == NULL) {
          //found insertion point
          parent->left = node;
          break;
        }
      }
      else {
        //we go right
        current = current->right;
        if(current == NULL) {
          //found insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
  updateDepths(root);
  ++size;
}

template <class T>
bool LazyBST<T>::contains(int key) {
  if(isEmpty()) {
    return false;
  }
  
  TreeNode<T> *current = root;
  
  while(current->key != key) {
    if(key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
    if(current == NULL) {
      return false;
    }
  }
  
  return true;
}

template <class T>
T LazyBST<T>::getValue(int key) {
  TreeNode<T> *current = root;
  
  while(current->key != key) {
    if(key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  
  return current->value;
}

template <class T>
bool LazyBST<T>::deleteNode(int k) {
  if(isEmpty()) {
    return false;
  }

  TreeNode<T> *current = root;
  TreeNode<T> *parent = root;
  bool isLeft = true;

  while(current->key != k) {
    parent = current;
    
    if(k < current->key) {
      isLeft = true;
      current = current->left;
    }
    else{
      isLeft = false;
      current = current->right;
    }
    if(current == NULL) {
      return false;
    }
  }

  //we found node that needs to be deleted, now lets proceeed to delete

  /* no children, it's a leaf node */
  if(current->left == NULL && current->right == NULL) {
    
    if(current == root) {
      root = NULL;
    }
    else if(isLeft) {
      parent->left = NULL;
    }
    else {
      parent->right = NULL;
    }
  }
  
  /* has one child */
  //has left child
  else if(current->right == NULL) {
    if(current == root) {
      root = current->left;
    }
    else if(isLeft){
      parent->left = current->left;
    }
    else {
      parent->right = current->right;
    }
  }

  //has right child
  else if(current->left == NULL) {
    if(current == root) {
      root = current->right;
    }
    else if(isLeft){
      parent->left = current->right;
    }
    else {
      parent->right = current->right;
    }
  }

  /* has two children */
  else {
    TreeNode<T> *successor = getSuccessor(current);
    
    if(current == root) {
      root = successor;
    }
    else if(isLeft) {
      parent->left = successor;
    }
    else {
      parent->right = successor;
    }
    successor->left = current->left;
    current->left = NULL;
    current->right = NULL;
  }
  delete current;
  --size;
  return true;
}

template <class T>
TreeNode<T> *LazyBST<T>::getSuccessor(TreeNode<T> *nodeToBeDeleted) {
  
  TreeNode<T> *successorParent = nodeToBeDeleted;
  TreeNode<T> *successor = nodeToBeDeleted;
  TreeNode<T> *current = nodeToBeDeleted->right;

  while(current != NULL) {
    successorParent = successor;
    successor = current;
    current = current->left;
  }

  //we found the successor but we need to check if the successor is a descendant of the right child
  if(successor != nodeToBeDeleted->right) {
    successorParent->left = successor->right;
    successor->right = nodeToBeDeleted->right;
  }

  return successor;
}
#endif