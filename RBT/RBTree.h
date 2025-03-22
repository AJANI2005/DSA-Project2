//
//  RBTree.h
//  RBT
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.
//

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <string>
using namespace std;

class RBTNode {
private:
  int data;
  char color;

  RBTNode *leftPtr;
  RBTNode *rightPtr;
  RBTNode *parentPtr;

public:
  // Constructor functions
  RBTNode() {
    rightPtr = leftPtr = parentPtr = NULL;
    color = 'R';
  }
  RBTNode(int val) {
    data = val;
    rightPtr = leftPtr = parentPtr = NULL;
    color = 'R';
  }

  // Mutator functions
  void setData(int val) { data = val; }
  void setColor(char col) { color = col; }
  void setLeftPtr(RBTNode *ptr) { leftPtr = ptr; }
  void setRightPtr(RBTNode *ptr) { rightPtr = ptr; }
  void setParentPtr(RBTNode *ptr) { parentPtr = ptr; }

  // Accessor functions
  int getData() { return data; }
  char getColor() { return color; }
  RBTNode *getLeftPtr() { return leftPtr; }
  RBTNode *getRightPtr() { return rightPtr; }
  RBTNode *getParentPtr() { return parentPtr; }
  int max_depth() const;
};

int RBTNode::max_depth() const {
  const int left_depth = leftPtr ? leftPtr->max_depth() : 0;
  const int right_depth = rightPtr ? rightPtr->max_depth() : 0;
  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

//===========================================================================
//================= End RBTNode Definition =================================
//===========================================================================

class RBT {
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
  RBTNode *findNode(int);
  RBTNode *getMinimum(RBTNode *);
  RBTNode *getSuccessor(RBTNode *);

public:
  // Constructor function
  RBT() { root = NULL; }

  // Mutator functions
  void insert(int);
  void remove(int);

  // Accessor functions
  RBTNode *getRoot() { return root; }
  string inOrder();
  string preOrder();
  string postOrder();
  string showLevels();
  int get_max_depth() const { return root ? root->max_depth() : 0; }
};

void RBT::rotateLeft(RBTNode *ptr) {
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

void RBT::rotateRight(RBTNode *ptr) {
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

RBTNode *RBT::findNode(int data) {
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

void RBT::insert(int val) {

  RBTNode *newnode = new RBTNode(val); // Create the new node

  if (root == NULL) // Tree is empty - newnode is first node
  {
    newnode->setColor('B');
    root = newnode;
    return;
  } else // Tree is NOT empty
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

void RBT::fixUp(RBTNode *ptr) {
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

void RBT::remove(int val) {
  RBTNode *markedNode = findNode(val);
  deleteNode(markedNode);
}

void RBT::deleteNode(RBTNode *node2Zap) {
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
      node2Zap->setData(successor->getData());

    // Finally... If color is black call fixup otherwise no fixup required
    if (successor->getColor() == 'B' && successorChild != NULL)
      fixUp(successorChild);
  }
}

RBTNode *RBT::getSuccessor(RBTNode *ptr) {
  if (ptr->getRightPtr() == NULL)
    return ptr->getLeftPtr();
  else
    return (getMinimum(ptr->getRightPtr()));
}

RBTNode *RBT::getMinimum(RBTNode *ptr) {
  while (ptr->getLeftPtr() != NULL)
    ptr = ptr->getLeftPtr();

  return ptr;
}

string RBT::inOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(inOrderHelper(ptr->getLeftPtr()));

    str.append(to_string(ptr->getData()));
    str.append("  ");

    str.append(inOrderHelper(ptr->getRightPtr()));
  }
  return str;
}

string RBT::preOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(to_string(ptr->getData()));
    str.append("  ");

    str.append(preOrderHelper(ptr->getLeftPtr()));
    str.append(preOrderHelper(ptr->getRightPtr()));
  }
  return str;
}

string RBT::postOrderHelper(RBTNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(postOrderHelper(ptr->getLeftPtr()));
    str.append(postOrderHelper(ptr->getRightPtr()));

    str.append(to_string(ptr->getData()));
    str.append("  ");
  }
  return str;
}

string RBT::inOrder() { return inOrderHelper(root); }

string RBT::preOrder() { return preOrderHelper(root); }

string RBT::postOrder() { return postOrderHelper(root); }

#endif /* defined(RBTREE_H) */
