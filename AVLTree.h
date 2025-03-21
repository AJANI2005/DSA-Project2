/*
    Name: Ajani Small
    ID: 400017967
    Date: 21 Mar,2025
    Purpose:
    This file contains the definition of the AVL Tree and its
    Node class.
*/

#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>
using namespace std;
class AVLNode {
private:
  int height;

  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;
  string key;
  AVLNode *left;
  AVLNode *right;

public:
  // constructor
  AVLNode(string _month, int _year, string _artist, string _title,
          string _recordLbl, int _weeksAtNumberOne);

  // Mutator functions
  void copyData(AVLNode *n);
  void setHeight(int ht) { height = ht; }
  void setLeft(AVLNode *ptr) { left = ptr; }
  void setRight(AVLNode *ptr) { right = ptr; }

  // Accessor functions
  string getRecord();
  string getData() { return key; }
  int getHeight() { return height; }
  AVLNode *getLeft() { return left; }
  AVLNode *getRight() { return right; }
};

// initialization constructor for AVLNode
AVLNode::AVLNode(string _month, int _year, string _artist, string _title,
                 string _recordLbl, int _weeksAtNumberOne) {
  month = _month;
  year = _year;
  artist = _artist;
  title = _title;
  recordLabel = _recordLbl;
  weeksAtNumberOne = _weeksAtNumberOne;
  key = title; // important
}
// copies data from one node to another
void AVLNode::copyData(AVLNode *n) {
  month = n->month;
  year = n->year;
  artist = n->artist;
  title = n->title;
  recordLabel = n->recordLabel;
  weeksAtNumberOne = n->weeksAtNumberOne;
  key = title; // important
}

string AVLNode::getRecord() {
  string record = "";
  record.append(month);
  record.append("\t");
  record.append(to_string(year));
  record.append("\t");
  record.append(artist);
  record.append("\t");
  record.append(title);
  record.append("\t");
  record.append(recordLabel);
  record.append("\t");
  record.append(to_string(weeksAtNumberOne));
  return record;
}

class AVLTree {
private:
  AVLNode *root;

  AVLNode *insertHelper(AVLNode *,
                        AVLNode *); // Recursive counterpart of insert
  AVLNode *removeNodeHelper(AVLNode *,
                            AVLNode *); // Recursive counterpart of delete
  string preOrderHelper(AVLNode *);     // Recursive counterpart of preorder
  string postOrderHelper(AVLNode *);    // Recursive counterpart of postorder
  string inOrderHelper(AVLNode *);      // Recursive counterpart of inorder
  AVLNode *rotateRight(AVLNode *);
  AVLNode *rotateLeft(AVLNode *);
  AVLNode *rotateDoubleRight(AVLNode *);
  AVLNode *rotateDoubleLeft(AVLNode *);
  AVLNode *rotateLeftRight(AVLNode *);
  AVLNode *rotateRightLeft(AVLNode *);
  int calcHeight(AVLNode *);
  int calcBalance(AVLNode *);

public:
  AVLTree() { root = NULL; }

  AVLNode *getRoot() { return root; }
  void insert(AVLNode *node) { root = insertHelper(root, node); }
  void remove(AVLNode *node) { root = removeNodeHelper(root, node); }
  string preOrder() { return preOrderHelper(root); }
  string postOrder() { return postOrderHelper(root); }
  string inOrder() { return inOrderHelper(root); }
  void purge() { root = NULL; }
};

AVLNode *AVLTree::insertHelper(AVLNode *ptr, AVLNode *node) {
  if (ptr == NULL) {
    ptr = node;
  }

  else // Tree is is not empty
  {
    if (node->getData() >=
        ptr->getData()) // insert in right subtree; OP definition
    {
      ptr->setRight(insertHelper(ptr->getRight(), node));
      if (calcBalance(ptr) == -2) // Too heavy on the right
      {
        if (node->getData() >
            (ptr->getRight())->getData()) // Regular right-heavy
          ptr = rotateDoubleRight(ptr);
        else // It's a special case: ">"
          ptr = rotateRightLeft(ptr);
      }
    }

    else if (node->getData() <
             ptr->getData()) // Insert it in ptr's left subtree
    {
      ptr->setLeft(insertHelper(ptr->getLeft(), node));
      if (calcBalance(ptr) == 2) // Too heavy on the left
      {
        if (node->getData() < (ptr->getLeft())->getData()) // Regular left-heavy
          ptr = rotateDoubleLeft(ptr);
        else // It's a special case: "<"
          ptr = rotateLeftRight(ptr);
      }
    }

    ptr->setHeight(calcHeight(ptr));
  }

  return (ptr);
}

AVLNode *AVLTree::removeNodeHelper(AVLNode *ptr, AVLNode *node) {

  if (ptr == NULL) // Node location is empty
  {
    return NULL;
  }

  // else the tree/subtree is not empty
  AVLNode *successor;

  if (node->getData() > ptr->getData()) // Search in Right sub-tree of ptr
  {
    ptr->setRight(removeNodeHelper(ptr->getRight(), node));
    if (calcBalance(ptr) == 2) // Subtree is too heavy on the left of ptr
    {
      if (calcBalance(ptr->getLeft()) >= 0)
        ptr = rotateDoubleLeft(ptr);
      else
        ptr = rotateLeftRight(ptr);
    }
  } else if (node->getData() < ptr->getData()) // Search the Left sub-tree
  {
    ptr->setLeft(removeNodeHelper(ptr->getLeft(), node));
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

      ptr->copyData(successor);
      ptr->setRight(removeNodeHelper(ptr->getRight(), ptr));
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

AVLNode *AVLTree::rotateRight(AVLNode *ptr) {
  AVLNode *newParent;

  newParent = ptr->getLeft();
  ptr->setLeft(newParent->getRight());
  newParent->setRight(ptr);
  ptr->setHeight(calcHeight(ptr));
  newParent->setHeight(calcHeight(newParent));

  return (newParent);
}

AVLNode *AVLTree::rotateLeft(AVLNode *ptr) {
  AVLNode *newParent;

  newParent = ptr->getRight();
  ptr->setRight(newParent->getLeft());
  newParent->setLeft(ptr);
  ptr->setHeight(calcHeight(ptr));
  newParent->setHeight(calcHeight(newParent));

  return (newParent);
}

AVLNode *AVLTree::rotateDoubleRight(AVLNode *ptr) {
  ptr = rotateLeft(ptr);
  return (ptr);
}

AVLNode *AVLTree::rotateDoubleLeft(AVLNode *ptr) {
  ptr = rotateRight(ptr);
  return (ptr);
}

// Special case - Less than sign config
AVLNode *AVLTree::rotateLeftRight(AVLNode *ptr) {
  ptr->setLeft(rotateLeft(ptr->getLeft()));
  ptr = rotateRight(ptr);
  return (ptr);
}

// Special case - Greater than sign config
AVLNode *AVLTree::rotateRightLeft(AVLNode *ptr) {
  ptr->setRight(rotateRight(ptr->getRight()));
  ptr = rotateLeft(ptr);
  return (ptr);
}

int AVLTree::calcHeight(AVLNode *ptr) {
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

int AVLTree::calcBalance(AVLNode *ptr) {
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

string AVLTree::inOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(inOrderHelper(ptr->getLeft()));

    str.append(ptr->getRecord());
    str.append("\n");

    str.append(inOrderHelper(ptr->getRight()));
  }
  return str;
}

string AVLTree::preOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(ptr->getRecord());
    str.append("\n");

    str.append(preOrderHelper(ptr->getLeft()));
    str.append(preOrderHelper(ptr->getRight()));
  }
  return str;
}

string AVLTree::postOrderHelper(AVLNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(postOrderHelper(ptr->getLeft()));
    str.append(postOrderHelper(ptr->getRight()));

    str.append(ptr->getRecord());
    str.append("\n");
  }
  return str;
}

#endif // AVLTree_H
