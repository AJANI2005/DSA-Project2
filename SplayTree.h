/*
    Name: Ajani Small
    ID: 400017967
    Date: 26 Mar,2025
    Purpose:
    SplayTree.h,SplayNode.h
    This file contains the definition of the Splay Tree  and its
    Node classes.
*/

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <string>
using namespace std;

class SplayNode {
private:
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;

  string key;

public:
  SplayNode *left;  // pointer to left subtree
  SplayNode *right; // pointer to right subtree

  // constructor
  SplayNode(string _month, int _year, string _artist, string _title,
            string _recordLbl, int _weeksAtNumberOne);

  SplayNode() { left = right = NULL; }

  // Accessors
  string getData() { return key; }
  SplayNode *getLeft() { return left; }
  SplayNode *getRight() { return right; }
  string getRecord();

  // Mutators
  void copyData(SplayNode *ptr);
  void setLeft(SplayNode *ptr) { left = ptr; }
  void setRight(SplayNode *ptr) { right = ptr; }
};

// initialization constructor for SplayNode
SplayNode::SplayNode(string _month, int _year, string _artist, string _title,
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
void SplayNode::copyData(SplayNode *n) {
  month = n->month;
  year = n->year;
  artist = n->artist;
  title = n->title;
  recordLabel = n->recordLabel;
  weeksAtNumberOne = n->weeksAtNumberOne;
  key = title; // important
}

string SplayNode::getRecord() {
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

class SplayTree {
private:
  SplayNode *root;

  // Utility functions
  SplayNode *RightRotate(SplayNode *);
  SplayNode *LeftRotate(SplayNode *);
  SplayNode *Splay(string, SplayNode *);
  SplayNode *insertHelper(SplayNode *, SplayNode *);

  string InOrderHelper(SplayNode *);
  string PreOrderHelper(SplayNode *);
  string PostOrderHelper(SplayNode *);
  void insertSplayNodeHelper(SplayNode **, SplayNode *);
  string displayNodesHelper(SplayNode *) const;

  void deleteSplayNode(SplayNode *);
  SplayNode *findSplayNode(string);
  SplayNode *getSuccessor(SplayNode *);
  SplayNode *getParent(SplayNode *);
  SplayNode *getMinimum(SplayNode *);

public:
  SplayTree() { root = NULL; };

  SplayNode *getRoot() { return root; }
  void insert(SplayNode *);
  string InOrder() { return InOrderHelper(root); }
  string PreOrder() { return PreOrderHelper(root); }
  string PostOrder() { return PostOrderHelper(root); }
  void insertSplayNode(string);
  string displayNodes();
  void remove(string);
};

SplayNode *SplayTree::RightRotate(SplayNode *ptr) {
  SplayNode *leftchild = ptr->left;
  ptr->left = leftchild->right;
  leftchild->right = ptr;
  return leftchild;
}

SplayNode *SplayTree::LeftRotate(SplayNode *ptr) {
  SplayNode *rightchild = ptr->right;
  ptr->right = rightchild->left;
  rightchild->left = ptr;
  return rightchild;
}

SplayNode *SplayTree::Splay(string key, SplayNode *root) {
  if (root == NULL)
    return NULL;

  SplayNode *header = new SplayNode();

  SplayNode *LeftTreeMax = header;
  SplayNode *RightTreeMin = header;

  /* loop until root->left == NULL || root->right == NULL; then break!
   The zig/zag mode would only happen when cannot find key and will reach
   null on one side after RR or LL Rotation.
   */
  while (root->left != NULL || root->right != NULL) {
    if (key < root->getData()) {
      if (root->left == NULL)
        break;

      if (key < root->left->getData()) {
        root = RightRotate(root); /* Only zig-zig mode need to rotate once,
                                because zig-zag mode is handled as zig
                                mode, which doesn't require rotate,
                                just linking it to R Tree */
        if (!root->left)
          break;
      }

      /* Link to Right Tree */
      RightTreeMin->left = root;
      RightTreeMin = RightTreeMin->left;
      root = root->left;
      RightTreeMin->left = NULL;
    } else if (key > root->getData()) {
      if (root->right == NULL)
        break;
      if (key > root->right->getData()) {
        root = LeftRotate(root); /* only zag-zag mode need to rotate once,
                             because zag-zig mode is handled as zag
                             mode, which doesn't require rotate,
                             just linking it to L Tree */
        if (root->right == NULL)
          break;
      }
      /* Link to Left Tree */
      LeftTreeMax->right = root;
      LeftTreeMax = LeftTreeMax->right;
      root = root->right;
      LeftTreeMax->right = NULL;
    } else
      break;
  }
  /* assemble Left Tree, Middle Tree and Right tree together */
  LeftTreeMax->right = root->left;
  RightTreeMin->left = root->right;
  root->left = header->right;
  root->right = header->left;
  return root;
}

SplayNode *SplayTree::findSplayNode(string val) {
  SplayNode *ptr = root;

  while (ptr != NULL) {
    if (ptr->getData() == val) // Found it!
    {
      return ptr;
    }

    if (val < ptr->getData()) {
      ptr = ptr->left;
    } else {
      ptr = ptr->right;
    }
  }

  return NULL; // Tree is empty OR did not find it
}

SplayNode *SplayTree::getParent(SplayNode *ptr) {
  if (ptr == NULL)
    return NULL;

  if (ptr == root)
    return NULL;

  SplayNode *cur = root;

  while (cur != NULL) {
    if (cur->left == ptr || cur->right == ptr) // Found it!
    {
      return cur;
    } else {
      if (ptr->getData() < cur->getData())
        cur = cur->left;
      else
        cur = cur->right;
    }
  }
  return cur; // Parent for ptr is NOT found
}

SplayNode *SplayTree::getSuccessor(SplayNode *ptr) {
  if (ptr->right == NULL)
    return ptr->left;
  else
    return (getMinimum(ptr->right));
}

SplayNode *SplayTree::getMinimum(SplayNode *ptr) {
  while (ptr->left != NULL)
    ptr = ptr->left;

  return ptr;
}

SplayNode *SplayTree::insertHelper(SplayNode *node, SplayNode *root) {

  if (root == NULL) {
    return node;
  }

  SplayNode *parent_temp = new SplayNode();
  SplayNode *temp = root;

  while (temp != NULL) {
    parent_temp = temp;

    if (node->getData() <= temp->getData())
      temp = temp->left;
    else
      temp = temp->right;
  }

  if (node->getData() <= parent_temp->getData())
    parent_temp->left = node;
  else
    parent_temp->right = node;

  root = Splay(node->getData(), root);
  return (root);
}

void SplayTree::insert(SplayNode *node) { root = insertHelper(node, root); }

string SplayTree::InOrderHelper(SplayNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(InOrderHelper(ptr->left));

    str.append(ptr->getRecord());
    str.append("\n");

    str.append(InOrderHelper(ptr->right));
  }
  return str;
}

string SplayTree::PreOrderHelper(SplayNode *ptr) {
  string str = "";

  if (ptr != NULL) {

    str.append(ptr->getRecord());
    str.append("\n");

    str.append(PreOrderHelper(ptr->left));
    str.append(PreOrderHelper(ptr->right));
  }
  return str;
}

string SplayTree::PostOrderHelper(SplayNode *ptr) {
  string str = "";

  if (ptr != NULL) {
    str.append(PostOrderHelper(ptr->left));
    str.append(PostOrderHelper(ptr->right));

    str.append(ptr->getRecord());
    str.append("\n");
  }
  return str;
}

void SplayTree::remove(string str) {
  SplayNode *markedSplayNode = findSplayNode(str);
  deleteSplayNode(markedSplayNode);
}

void SplayTree::deleteSplayNode(SplayNode *node) {

  if (node == NULL) // If node is NULL then do nothing.
    return;
  else {
    SplayNode *successor, *successorChild, *parent;

    if (node->left == NULL || node->right == NULL)
      successor = node;
    else // node has 2 children
      successor = getSuccessor(node);

    successorChild = successor->right;
    parent = getParent(successor);

    // Transfer data from successor to node
    node->copyData(successor);

    if (parent == NULL)
      root = successorChild;
    else if (successor == parent->left)
      parent->left = successorChild;
    else
      parent->right = successorChild;

    if (successor != node)
      node->copyData(successor);

    delete successor;
  }
}

#endif
