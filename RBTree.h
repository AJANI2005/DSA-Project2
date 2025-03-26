/*
    Name: Ajani Small
    ID: 400017967
    Date: 22 Mar,2025
    Purpose:
    RBTree.h,RBTNode.h
    This file contains the definition of the Red Black Tree  and its
    Node classes.
*/

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <string>
using namespace std;

class RBTNode {
private:
  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;
  string key;
  char color;

  RBTNode *leftPtr;
  RBTNode *rightPtr;
  RBTNode *parentPtr;

public:
  // constructor
  RBTNode(string _month, int _year, string _artist, string _title,
          string _recordLbl, int _weeksAtNumberOne);
  RBTNode() { leftPtr = rightPtr = parentPtr = NULL; }

  // accessor functions
  void copyData(RBTNode *ptr);
  void setColor(char col) { color = col; }
  void setLeftPtr(RBTNode *ptr) { leftPtr = ptr; }
  void setRightPtr(RBTNode *ptr) { rightPtr = ptr; }
  void setParentPtr(RBTNode *ptr) { parentPtr = ptr; }
  string getRecord();

  // mutator functions
  string getData() { return key; }
  char getColor() { return color; }
  RBTNode *getLeftPtr() { return leftPtr; }
  RBTNode *getRightPtr() { return rightPtr; }
  RBTNode *getParentPtr() { return parentPtr; }
  int max_depth() const;
};

// initialization constructor for RBTNode
RBTNode::RBTNode(string _month, int _year, string _artist, string _title,
                 string _recordLbl, int _weeksAtNumberOne) {
  month = _month;
  year = _year;
  artist = _artist;
  title = _title;
  recordLabel = _recordLbl;
  weeksAtNumberOne = _weeksAtNumberOne;
  key = title; // important
  rightPtr = leftPtr = parentPtr = NULL;
  color = 'R';
}

int RBTNode::max_depth() const {
  const int left_depth = leftPtr ? leftPtr->max_depth() : 0;
  const int right_depth = rightPtr ? rightPtr->max_depth() : 0;
  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

// copies data from one node to another
void RBTNode::copyData(RBTNode *n) {
  month = n->month;
  year = n->year;
  artist = n->artist;
  title = n->title;
  recordLabel = n->recordLabel;
  weeksAtNumberOne = n->weeksAtNumberOne;
  key = title; // important
}

string RBTNode::getRecord() {
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

class RBTree {
private:
  RBTNode *root;

  // Utility functions
  void rotateLeft(RBTNode *);
  void rotateRight(RBTNode *);
  void fixUp(RBTNode *);
  string inOrderHelper(RBTNode *);
  string preOrderHelper(RBTNode *);
  string postOrderHelper(RBTNode *);
  void deleteNode(RBTNode *);
  RBTNode *findNode(string);
  RBTNode *getMinimum(RBTNode *);
  RBTNode *getSuccessor(RBTNode *);

public:
  // Constructor function
  RBTree() { root = NULL; }

  // Mutator functions
  void insert(RBTNode *);
  void remove(string);

  // Accessor functions
  RBTNode *getRoot() { return root; }
  string inOrder();
  string preOrder();
  string postOrder();
  string showLevels();
  int get_max_depth() const { return root ? root->max_depth() : 0; }
};

void RBTree::rotateLeft(RBTNode *ptr) {
  RBTNode *rightChild = ptr->getRightPtr();
  ptr->setRightPtr(rightChild->getLeftPtr());

  if (rightChild->getLeftPtr() != NULL)
    rightChild->getLeftPtr()->setParentPtr(ptr);

  rightChild->setParentPtr(ptr->getParentPtr());

  if (ptr == root)
    root = rightChild;
  else {
    if (ptr == ptr->getParentPtr()->getLeftPtr())
      ptr->getParentPtr()->setLeftPtr(rightChild);
    else
      ptr->getParentPtr()->setRightPtr(rightChild);
  }

  rightChild->setLeftPtr(ptr);
  ptr->setParentPtr(rightChild);
}

void RBTree::rotateRight(RBTNode *ptr) {
  RBTNode *leftChild = ptr->getLeftPtr();
  ptr->setLeftPtr(leftChild->getRightPtr());

  if (leftChild->getRightPtr() != NULL)
    leftChild->getRightPtr()->setParentPtr(ptr);

  leftChild->setParentPtr(ptr->getParentPtr());

  if (ptr == root)
    root = leftChild;
  else {
    if (ptr == ptr->getParentPtr()->getRightPtr())
      ptr->getParentPtr()->setRightPtr(leftChild);
    else
      ptr->getParentPtr()->setLeftPtr(leftChild);
  }

  leftChild->setRightPtr(ptr);
  ptr->setParentPtr(leftChild);
}

RBTNode *RBTree::findNode(string data) {
  RBTNode *ptr = root;

  while (ptr != NULL) {
    if (ptr->getData() == data) // Found it!
    {
      return ptr;
    }

    if (data < ptr->getData())
      ptr = ptr->getLeftPtr();
    else
      ptr = ptr->getRightPtr();
  }

  return NULL; // Tree is empty OR did not find it
}

void RBTree::insert(RBTNode *node) {

  // Create new node
  RBTNode *newnode = node;

  // Tree is empty - newnode is first node
  if (root == NULL) {
    newnode->setColor('B');
    root = newnode;
    return;
  } else
  // Tree is NOT empty
  {
    RBTNode *ancestor = NULL;
    RBTNode *current = root;

    while (current != NULL) {
      ancestor = current;

      if (newnode->getData() < current->getData())
        current = current->getLeftPtr();
      else
        current = current->getRightPtr();
    }

    newnode->setParentPtr(ancestor);

    if (newnode->getData() < ancestor->getData())
      ancestor->setLeftPtr(newnode);
    else
      ancestor->setRightPtr(newnode);

    fixUp(newnode);
  }
}

void RBTree::fixUp(RBTNode *ptr) {
  RBTNode *ptrsUncle = NULL;

  while (ptr != root && ptr->getParentPtr()->getColor() == 'R') {
    if (ptr->getParentPtr() ==
        ptr->getParentPtr()
            ->getParentPtr()
            ->getLeftPtr()) { // ptr's parent is a LEFT child
      ptrsUncle = ptr->getParentPtr()->getParentPtr()->getRightPtr();

      if (ptrsUncle != NULL && ptrsUncle->getColor() == 'R') {
        ptr->getParentPtr()->setColor('B');
        ptrsUncle->setColor('B');
        ptr->getParentPtr()->getParentPtr()->setColor('R');
        ptr = ptr->getParentPtr()->getParentPtr();
      } else {
        if (ptr == ptr->getParentPtr()->getRightPtr()) {
          ptr = ptr->getParentPtr();
          rotateLeft(ptr);
        }

        ptr->getParentPtr()->setColor('B');
        ptr->getParentPtr()->getParentPtr()->setColor('R');
        rotateRight(ptr->getParentPtr()->getParentPtr());
      }
    } else // ptr's parent is a RIGHT child
    {
      ptrsUncle = ptr->getParentPtr()->getParentPtr()->getLeftPtr();

      if (ptrsUncle != NULL && ptrsUncle->getColor() == 'R') {
        ptr->getParentPtr()->setColor('B');
        ptrsUncle->setColor('B');
        ptr->getParentPtr()->getParentPtr()->setColor('R');
        ptr = ptr->getParentPtr()->getParentPtr();
      } else {
        if (ptr == ptr->getParentPtr()->getLeftPtr()) {
          ptr = ptr->getParentPtr();
          rotateRight(ptr);
        }
        ptr->getParentPtr()->setColor('B');
        ptr->getParentPtr()->getParentPtr()->setColor('R');
        rotateLeft(ptr->getParentPtr()->getParentPtr());
      }
    }
  }

  root->setColor('B');

  ptrsUncle = NULL;
}

void RBTree::remove(string val) {
  RBTNode *markedNode = findNode(val);
  deleteNode(markedNode);
}

void RBTree::deleteNode(RBTNode *node2Zap) {
  if (node2Zap == NULL) // If node being deleted is NULL then do nothing.
    return;
  else {
    RBTNode *successor, *successorChild;
    successor = node2Zap;

    if (node2Zap->getLeftPtr() == NULL || node2Zap->getRightPtr() == NULL)
      // If either of the children is NULL
      successor = node2Zap;
    else // node2Zap has 2 children
      successor = getSuccessor(node2Zap);

    if (successor->getLeftPtr() == NULL)
      successorChild = successor->getRightPtr();
    else
      successorChild = successor->getRightPtr();

    if (successorChild != NULL)
      successorChild->setParentPtr(successor->getParentPtr());

    if (successor->getParentPtr() == NULL)
      root = successorChild;
    else if (successor == successor->getParentPtr()->getLeftPtr())
      successor->getParentPtr()->setLeftPtr(successorChild);
    else
      successor->getParentPtr()->setRightPtr(successorChild);

    if (successor != node2Zap)
      node2Zap->copyData(successor);

    // Finally... If color is black call fixup otherwise no fixup required
    if (successor->getColor() == 'B' && successorChild != NULL)
      fixUp(successorChild);
  }
}

RBTNode *RBTree::getSuccessor(RBTNode *ptr) {
  if (ptr->getRightPtr() == NULL)
    return ptr->getLeftPtr();
  else
    return (getMinimum(ptr->getRightPtr()));
}

RBTNode *RBTree::getMinimum(RBTNode *ptr) {
  while (ptr->getLeftPtr() != NULL)
    ptr = ptr->getLeftPtr();

  return ptr;
}

string RBTree::inOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(inOrderHelper(ptr->getLeftPtr()));

    str.append(ptr->getRecord());
    str.append("\n");

    str.append(inOrderHelper(ptr->getRightPtr()));
  }
  return str;
}

string RBTree::preOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(ptr->getRecord());
    str.append("\n");

    str.append(preOrderHelper(ptr->getLeftPtr()));
    str.append(preOrderHelper(ptr->getRightPtr()));
  }
  return str;
}

string RBTree::postOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(postOrderHelper(ptr->getLeftPtr()));
    str.append(postOrderHelper(ptr->getRightPtr()));

    str.append(ptr->getRecord());
    str.append("\n");
  }
  return str;
}

string RBTree::inOrder() { return inOrderHelper(root); }

string RBTree::preOrder() { return preOrderHelper(root); }

string RBTree::postOrder() { return postOrderHelper(root); }

#endif /* defined(RBTREE_H) */
