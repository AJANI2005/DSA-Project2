/*
    Name: Ajani Small
    ID: 400017967
    Date: 26 Mar,2025
    Purpose:
    MinHeap.h,MinHeapNode.h
    This file contains the definition of the Max Heap tree and its
    Node class.
*/

#ifndef MINHEAP_H
#define MINHEAP_H

#include <cmath>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class MinHeapNode {
public:
  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;

  MinHeapNode *left, *right, *parent;
  string key;

  // constructor
  MinHeapNode(string _month, int _year, string _artist, string _title,
              string _recordLbl, int _weeksAtNumberOne);
  MinHeapNode() { left = right = parent = NULL; };

  // accessor functions
  int count();
  string getData() { return key; }
  MinHeapNode *getLeft() { return left; }
  MinHeapNode *getRight() { return right; }
  int max_depth();
  string getRecord();

  // mutator functions
  void copyData(MinHeapNode *val);
  void setLeft(MinHeapNode *ptr);
  void setRight(MinHeapNode *ptr);
};

class MinHeap {
private:
  MinHeapNode *root;
  MinHeapNode *last;
  int size;

  void heapifyUp(MinHeapNode *node);
  void heapifyDown(MinHeapNode *node);
  void swapNodes(MinHeapNode *a, MinHeapNode *b);
  MinHeapNode *findNodeByValue(MinHeapNode *node, string value);
  void updateLastNode();
  MinHeapNode *getParentOfNewNode();
  void setParents(MinHeapNode *node, MinHeapNode *parent = NULL);

public:
  MinHeap();

  MinHeapNode *getRoot() { return root; }
  string getLast() { return last ? last->getData() : ""; }
  int getSize() { return size; }
  int get_max_depth() { return root ? root->max_depth() : 0; }

  void insert(MinHeapNode *node);
  void remove(string value);
  MinHeapNode *find(string value);
  string display();
  string displayHelper(MinHeapNode *node);
};

// MinHeapNode Implementation
MinHeapNode::MinHeapNode(string _month, int _year, string _artist,
                         string _title, string _recordLbl,
                         int _weeksAtNumberOne) {
  month = _month;
  year = _year;
  artist = _artist;
  title = _title;
  recordLabel = _recordLbl;
  weeksAtNumberOne = _weeksAtNumberOne;
  key = title;
  left = right = parent = NULL;
}

void MinHeapNode::copyData(MinHeapNode *val) {
  month = val->month;
  year = val->year;
  artist = val->artist;
  title = val->title;
  recordLabel = val->recordLabel;
  weeksAtNumberOne = val->weeksAtNumberOne;
  key = title;
}

string MinHeapNode::getRecord() {
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

int MinHeapNode::max_depth() {
  int left_depth = left ? left->max_depth() : 0;
  int right_depth = right ? right->max_depth() : 0;
  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int MinHeapNode::count() {
  return 1 + (left ? left->count() : 0) + (right ? right->count() : 0);
}

void MinHeapNode::setLeft(MinHeapNode *ptr) {
  left = ptr;
  if (ptr)
    ptr->parent = this;
}

void MinHeapNode::setRight(MinHeapNode *ptr) {
  right = ptr;
  if (ptr)
    ptr->parent = this;
}

// MinHeap Implementation
MinHeap::MinHeap() {
  root = last = NULL;
  size = 0;
}

void MinHeap::setParents(MinHeapNode *node, MinHeapNode *parent) {
  if (!node)
    return;
  node->parent = parent;
  setParents(node->left, node);
  setParents(node->right, node);
}

void MinHeap::insert(MinHeapNode *node) {
  if (!root) {
    root = last = node;
    size = 1;
    return;
  }

  MinHeapNode *parent = getParentOfNewNode();
  if (!parent->left) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
  last = node;
  size++;

  heapifyUp(node);
}

MinHeapNode *MinHeap::getParentOfNewNode() {
  if (size == 0)
    return NULL;

  int mask = 1 << ((int)log2(size + 1) - 1);
  MinHeapNode *current = root;

  while (mask > 1) {
    current = (size + 1) & mask ? current->right : current->left;
    mask >>= 1;
  }
  return current;
}

void MinHeap::heapifyUp(MinHeapNode *node) {
  while (node->parent && node->getData() < node->parent->getData()) {
    swapNodes(node, node->parent);
    node = node->parent;
  }
}

void MinHeap::heapifyDown(MinHeapNode *node) {
  while (node) {
    MinHeapNode *swapNode = node;

    if (node->left && node->left->getData() < swapNode->getData())
      swapNode = node->left;
    if (node->right && node->right->getData() < swapNode->getData())
      swapNode = node->right;

    if (swapNode == node)
      break;

    swapNodes(node, swapNode);
    node = swapNode;
  }
}

void MinHeap::swapNodes(MinHeapNode *a, MinHeapNode *b) {
  if (!a || !b)
    return;

  MinHeapNode temp;
  temp.copyData(a);
  a->copyData(b);
  b->copyData(&temp);
}

void MinHeap::remove(string value) {
  MinHeapNode *node = find(value);
  if (!node)
    return;

  node->copyData(last);

  MinHeapNode *lastParent = last->parent;
  if (lastParent) {
    if (lastParent->left == last) {
      lastParent->left = NULL;
    } else {
      lastParent->right = NULL;
    }
  }

  delete last;
  size--;

  updateLastNode();

  heapifyDown(node);
  heapifyUp(node);
}

void MinHeap::updateLastNode() {
  if (size == 0) {
    last = NULL;
    return;
  }

  int mask = 1 << ((int)log2(size)) - 1;
  MinHeapNode *current = root;

  while (mask > 0) {
    current = size & mask ? current->right : current->left;
    mask >>= 1;
  }

  last = current;
}

MinHeapNode *MinHeap::find(string value) {
  return findNodeByValue(root, value);
}

MinHeapNode *MinHeap::findNodeByValue(MinHeapNode *node, string value) {
  if (!node)
    return NULL;
  if (node->getData() == value)
    return node;

  MinHeapNode *found = findNodeByValue(node->left, value);
  if (found)
    return found;

  return findNodeByValue(node->right, value);
}

string MinHeap::display() { return displayHelper(root); }

string MinHeap::displayHelper(MinHeapNode *node) {
  string out = "";
  if (node == nullptr)
    return out;

  queue<MinHeapNode *> q;
  q.push(node); // Start with the root node

  while (!q.empty()) {
    MinHeapNode *currentNode = q.front();
    q.pop();

    out.append(currentNode->getRecord());
    out.append("\n");

    if (currentNode->getLeft()) {
      q.push(currentNode->getLeft());
    }
    if (currentNode->getRight()) {
      q.push(currentNode->getRight());
    }
  }
  return out;
}
#endif /* MINHEAP_H */
