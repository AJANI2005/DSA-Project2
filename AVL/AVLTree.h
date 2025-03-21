//
//  AVLTree.h
//  AVL
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.

#ifndef AVL_AVLTree_H
#define AVL_AVLTree_H
#include <cstddef>
#include <iostream>
using namespace std;
class AVLNode {
private:
  int data;
  int height;

public:
  AVLNode *left;
  AVLNode *right;

  // Constructor functions
  AVLNode() {
    data = -99;
    height = 0;
    right = left = NULL;
  }
  AVLNode(int val) {
    data = val;
    height = 0;
    right = left = NULL;
  }

  // Mutator functions
  void setData(int val) { data = val; }
  void setHeight(int ht) { height = ht; }
  void setLeft(AVLNode *ptr) { left = ptr; }
  void setRight(AVLNode *ptr) { right = ptr; }

  // Accessor functions
  int getData() { return data; }
  int getHeight() { return height; }
  AVLNode *getLeft() { return left; }
  AVLNode *getRight() { return right; }
};

class AVL {
private:
  AVLNode *root;

  AVLNode *insertHelper(AVLNode *, int);     // Recursive counterpart of insert
  AVLNode *removeNodeHelper(AVLNode *, int); // Recursive counterpart of delete
  string preOrderHelper(AVLNode *);  // Recursive counterpart of preorder
  string postOrderHelper(AVLNode *); // Recursive counterpart of postorder
  string inOrderHelper(AVLNode *);   // Recursive counterpart of inorder
  AVLNode *rotateRight(AVLNode *);
  AVLNode *rotateLeft(AVLNode *);
  AVLNode *rotateDoubleRight(AVLNode *);
  AVLNode *rotateDoubleLeft(AVLNode *);
  AVLNode *rotateLeftRight(AVLNode *);
  AVLNode *rotateRightLeft(AVLNode *);
  int calcHeight(AVLNode *);
  int calcBalance(AVLNode *);

public:
  AVL() { root = NULL; }

  AVLNode *getRoot() { return root; }
  void insert(int val) { root = insertHelper(root, val); }
  void remove(int val) { root = removeNodeHelper(root, val); }
  string preOrder() { return preOrderHelper(root); }
  string postOrder() { return postOrderHelper(root); }
  string inOrder() { return inOrderHelper(root); }
  void purge() { root = NULL; }
};

AVLNode *AVL::insertHelper(AVLNode *ptr, int val) {
  if (ptr == NULL) {
    ptr = new AVLNode(val);
  }

  else // Tree is is not empty
  {
    if (val >= ptr->getData()) // insert in right subtree; OP definition
    {
      ptr->setRight(insertHelper(ptr->getRight(), val));
      if (calcBalance(ptr) == -2) // Too heavy on the right
      {
        if (val > (ptr->getRight())->getData()) // Regular right-heavy
          ptr = rotateDoubleRight(ptr);
        else // It's a special case: ">"
          ptr = rotateRightLeft(ptr);
      }
    }

    else if (val < ptr->getData()) // Insert it in ptr's left subtree
    {
      ptr->setLeft(insertHelper(ptr->getLeft(), val));
      if (calcBalance(ptr) == 2) // Too heavy on the left
      {
        if (val < (ptr->getLeft())->getData()) // Regular left-heavy
          ptr = rotateDoubleLeft(ptr);
        else // It's a special case: "<"
          ptr = rotateLeftRight(ptr);
      }
    }

    ptr->setHeight(calcHeight(ptr));
  }

  return (ptr);
}

AVLNode *AVL::removeNodeHelper(AVLNode *ptr, int val) {

  if (ptr == NULL) // Node location is empty
  {
    return NULL;
  }

  // else the tree/subtree is not empty
  AVLNode *successor;

  if (val > ptr->getData()) // Search in Right sub-tree of ptr
  {
    ptr->setRight(removeNodeHelper(ptr->getRight(), val));
    if (calcBalance(ptr) == 2) // Subtree is too heavy on the left of ptr
    {
      if (calcBalance(ptr->getLeft()) >= 0)
        ptr = rotateDoubleLeft(ptr);
      else
        ptr = rotateLeftRight(ptr);
    }
  } else if (val < ptr->getData()) // Search the Left sub-tree
  {
    ptr->setLeft(removeNodeHelper(ptr->getLeft(), val));
    if (calcBalance(ptr) == -2) // Rebalance: ptr is too heavy on the right
    {
      if (calcBalance(ptr->getRight()) <= 0)
        ptr = rotateDoubleRight(ptr);
      else
        ptr = rotateRightLeft(ptr);
    }
  } else {
    // Node to to be deleted is found
    if (ptr->getRight() != NULL) { // Go right and deep left
      successor = ptr->getRight();
      while (successor->getLeft() != NULL)
        successor = successor->getLeft();

      ptr->setData(successor->getData());
      ptr->setRight(removeNodeHelper(ptr->getRight(), ptr->getData()));
      if (calcBalance(ptr) == 2) // Rebalance: ptr is too heavy on the left
      {
        if (calcBalance(ptr->getLeft()) >= 0)
          ptr = rotateDoubleLeft(ptr);
        else
          ptr = rotateLeftRight(ptr);
      }
    } else
      return (ptr->getLeft());
  }
  ptr->setHeight(calcHeight(ptr));
  return (ptr);
}

AVLNode *AVL::rotateRight(AVLNode *ptr) {
  AVLNode *newParent;

  newParent = ptr->getLeft();
  ptr->setLeft(newParent->getRight());
  newParent->setRight(ptr);
  ptr->setHeight(calcHeight(ptr));
  newParent->setHeight(calcHeight(newParent));

  return (newParent);
}

AVLNode *AVL::rotateLeft(AVLNode *ptr) {
  AVLNode *newParent;

  newParent = ptr->getRight();
  ptr->setRight(newParent->getLeft());
  newParent->setLeft(ptr);
  ptr->setHeight(calcHeight(ptr));
  newParent->setHeight(calcHeight(newParent));

  return (newParent);
}

AVLNode *AVL::rotateDoubleRight(AVLNode *ptr) {
  ptr = rotateLeft(ptr);
  return (ptr);
}

AVLNode *AVL::rotateDoubleLeft(AVLNode *ptr) {
  ptr = rotateRight(ptr);
  return (ptr);
}

// Special case - Less than sign config
AVLNode *AVL::rotateLeftRight(AVLNode *ptr) {
  ptr->setLeft(rotateLeft(ptr->getLeft()));
  ptr = rotateRight(ptr);
  return (ptr);
}

// Special case - Greater than sign config
AVLNode *AVL::rotateRightLeft(AVLNode *ptr) {
  ptr->setRight(rotateRight(ptr->getRight()));
  ptr = rotateLeft(ptr);
  return (ptr);
}

int AVL::calcHeight(AVLNode *ptr) {
  int leftHeight, rightHeight;

  if (ptr == NULL)
    return (0);

  if (ptr->getLeft() == NULL)
    leftHeight = 0;
  else
    leftHeight = 1 + ptr->getLeft()->getHeight();

  if (ptr->getRight() == NULL)
    rightHeight = 0;
  else
    rightHeight = 1 + ptr->getRight()->getHeight();

  if (leftHeight > rightHeight)
    return (leftHeight);

  return (rightHeight);
}

int AVL::calcBalance(AVLNode *ptr) {
  int leftHeight, rightHeight;

  if (ptr == NULL)
    return (0);

  if (ptr->getLeft() == NULL)
    leftHeight = 0;
  else
    leftHeight = 1 + ptr->getLeft()->getHeight();

  if (ptr->getRight() == NULL)
    rightHeight = 0;
  else
    rightHeight = 1 + ptr->getRight()->getHeight();

  return (leftHeight - rightHeight);
}

string AVL::inOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(inOrderHelper(ptr->getLeft()));

    str.append(to_string(ptr->getData()));
    str.append("  ");

    str.append(inOrderHelper(ptr->getRight()));
  }
  return str;
}

string AVL::preOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(to_string(ptr->getData()));
    str.append("  ");

    str.append(preOrderHelper(ptr->getLeft()));
    str.append(preOrderHelper(ptr->getRight()));
  }
  return str;
}

string AVL::postOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(postOrderHelper(ptr->getLeft()));
    str.append(postOrderHelper(ptr->getRight()));

    str.append(to_string(ptr->getData()));
    str.append("  ");
  }
  return str;
}

#endif // defined(AVL_AVLTree_H)
