/*
    Name: Ajani Small
    ID: 400017967
    Date: 17 Mar,2025
    Purpose:
    BSTree.h,BSTNode.h
    This file contains the definition of the Binary Search Tree (BST) and its
    Node classes.
*/

#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <string>
using namespace std;
class BSTNode {
  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;
  BSTNode *left;
  BSTNode *right;

  string key;

public:
  // constructor
  BSTNode(string _month, int _year, string _artist, string _title,
          string _recordLbl, int _weeksAtNumberOne);
  BSTNode() { left = right = NULL; }

  // accessor functions
  string getData() { return key; }
  BSTNode *getLeft() { return left; }
  BSTNode *getRight() { return right; }
  string getRecord();

  // mutator functions
  void setLeft(BSTNode *l) { left = l; }
  void setRight(BSTNode *r) { right = r; }
  void copyData(BSTNode *n);
};

// initialization constructor for BSTNode
BSTNode::BSTNode(string _month, int _year, string _artist, string _title,
                 string _recordLbl, int _weeksAtNumberOne) {
  month = _month;
  year = _year;
  artist = _artist;
  title = _title;
  recordLabel = _recordLbl;
  weeksAtNumberOne = _weeksAtNumberOne;
  key = title; // important
  left = right = NULL;
}

// copies data from one node to another
void BSTNode::copyData(BSTNode *n) {
  month = n->month;
  year = n->year;
  artist = n->artist;
  title = n->title;
  recordLabel = n->recordLabel;
  weeksAtNumberOne = n->weeksAtNumberOne;
  key = title; // important
}

string BSTNode::getRecord() {
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

class BSTree {
private:
  BSTNode *root;

  // helper functions for insertion and deletion
  BSTNode *successor(BSTNode *node);

  BSTNode *insertHelper(BSTNode *root, BSTNode *node);
  BSTNode *removeHelper(BSTNode *root, string data);

  string inOrderHelper(BSTNode *node);
  string preOrderHelper(BSTNode *root);
  string postOrderHelper(BSTNode *node);

public:
  // constructors
  BSTree() { root = NULL; }
  BSTree(BSTNode *root) : root(root) {}

  // display functions
  string inOrder();
  string preOrder();
  string postOrder();

  // accessor functions
  BSTNode *getRoot() { return root; }

  // finds a node in
  BSTNode *findNode(string data);
  // mutator functions
  // inserts a node into the tree
  BSTNode *insert(BSTNode *node);
  // removes a node from the tree
  BSTNode *remove(string data);
};

string BSTree::inOrder() { return inOrderHelper(root); }
string BSTree::inOrderHelper(BSTNode *node) {
  string out = "";
  if (node != NULL) {
    out.append(inOrderHelper(node->getLeft()));
    out.append(node->getRecord());
    out.append("\n");
    out.append(inOrderHelper(node->getRight()));
  }
  return out;
}

string BSTree::preOrder() { return preOrderHelper(root); }
string BSTree::preOrderHelper(BSTNode *node) {
  string out = "";
  if (node != NULL) {
    out.append(node->getRecord());
    out.append("\n");
    out.append(preOrderHelper(node->getLeft()));
    out.append(preOrderHelper(node->getRight()));
  }
  return out;
}
string BSTree::postOrder() { return postOrderHelper(root); }
string BSTree::postOrderHelper(BSTNode *node) {
  string out = "";
  if (node != NULL) {
    out.append(postOrderHelper(node->getLeft()));
    out.append(postOrderHelper(node->getRight()));
    out.append(node->getRecord());
    out.append("\n");
  }
  return out;
}

BSTNode *BSTree::insert(BSTNode *node) {
  if (root == NULL) {
    root = node;
    return root;
  }
  return insertHelper(root, node);
}

BSTNode *BSTree::insertHelper(BSTNode *ptr, BSTNode *node) {
  // case 1 : tree is empty , set ptr to node
  if (ptr == NULL) {
    return node;
  }
  // case 2 : node data is greater than or equal to  ptr
  else if (node->getData() >= ptr->getData()) {
    // recursively in right subtree
    ptr->setRight(insertHelper(ptr->getRight(), node));
  }
  // case 3 : node data is less than to  ptr
  else if (node->getData() < ptr->getData()) {
    // recursively in left subtree
    ptr->setLeft(insertHelper(ptr->getLeft(), node));
  }

  return ptr;
}

BSTNode *BSTree::remove(string data) {
  if (findNode(data) != NULL) {
    return removeHelper(root, data);
  } else {
    cout << "Node with data," << data << ", not found in the tree" << endl;
    return NULL;
  }
}
BSTNode *BSTree::removeHelper(BSTNode *ptr, string data) {

  // case 1 : tree is empty , set ptr to node
  if (ptr == NULL) {
    return ptr;
  }
  // case 2 :  data is greater than the data in ptr
  else if (data > ptr->getData()) {
    ptr->setRight(removeHelper(ptr->getRight(), data));
  }
  // case 3 :  data is less than the data in  ptr
  else if (data < ptr->getData()) {
    ptr->setLeft(removeHelper(ptr->getLeft(), data));
  } else {
    // case 4 : ptr is the node to delete

    // case 4 - 1 : ptr has no children
    if (ptr->getLeft() == NULL && ptr->getRight() == NULL) {
      // just delete the node
      delete ptr;
      ptr = NULL;
    }

    // case 4 - 2 : ptr has both children
    else if (ptr->getRight() != NULL && ptr->getLeft() != NULL) {
      BSTNode *temp = successor(ptr);
      ptr->copyData(temp);
      ptr->setRight(removeHelper(ptr->getRight(), temp->getData()));
    }

    // case 4 - 3 : ptr has only one child
    else {
      BSTNode *child =
          (ptr->getLeft() != NULL) ? ptr->getLeft() : ptr->getRight();
      delete ptr;
      return child;
    }
  }
  return ptr;
}

BSTNode *BSTree::successor(BSTNode *node) {
  // find the lowest value below the right child of this node
  BSTNode *ptr = node->getRight();
  while (ptr->getLeft() != NULL) {
    ptr = ptr->getLeft();
  }
  return ptr;
}

BSTNode *BSTree::findNode(string data) {
  BSTNode *node = root;
  while (node != NULL) {
    // case 1: we found the node
    if (node->getData() == data) {
      return node;
    }
    // case 2: data is greater than the data of the current node
    else if (data >= node->getData()) {
      node = node->getRight();
    }
    // case 3: data is less than the data of the current node
    else if (data < node->getData()) {
      node = node->getLeft();
    }
  }
  // case 4: we havent found the node
  return NULL;
}
#endif // BSTREE_H
