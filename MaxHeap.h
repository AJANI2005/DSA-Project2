/*
    Name: Ajani Small
    ID: 400017967
    Date: 26 Mar,2025
    Purpose:
    MaxHeap.h,MaxHeapNode.h
    This file contains the definition of the Max Heap tree and its
    Node class.
*/

#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <cmath>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class MaxHeapNode {
public:
  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;

  MaxHeapNode *left, *right, *parent;
  string key;

  // constructor
  MaxHeapNode(string _month, int _year, string _artist, string _title,
              string _recordLbl, int _weeksAtNumberOne);
  MaxHeapNode() { left = right = parent = NULL; };

  // accessor functions
  int count();
  string getData() { return key; }
  MaxHeapNode *getLeft() { return left; }
  MaxHeapNode *getRight() { return right; }
  int max_depth();
  string getRecord();

  // mutator functions
  void copyData(MaxHeapNode *val);
  void setLeft(MaxHeapNode *ptr);
  void setRight(MaxHeapNode *ptr);
};

class MaxHeap {
private:
  MaxHeapNode *root;
  MaxHeapNode *last;
  int size;

  void heapifyUp(MaxHeapNode *node);
  void heapifyDown(MaxHeapNode *node);
  void swapNodes(MaxHeapNode *a, MaxHeapNode *b);
  MaxHeapNode *findNodeByValue(MaxHeapNode *node, string value);
  void updateLastNode();
  MaxHeapNode *getParentOfNewNode();
  void setParents(MaxHeapNode *node, MaxHeapNode *parent = NULL);

public:
  MaxHeap();

  MaxHeapNode *getRoot() { return root; }
  string getLast() { return last ? last->getData() : ""; }
  int getSize() { return size; }
  int get_max_depth() { return root ? root->max_depth() : 0; }

  void insert(MaxHeapNode *node);
  void remove(string value);
  MaxHeapNode *find(string value);
  string display();
  string displayHelper(MaxHeapNode *node);
};

// MaxHeapNode Implementation
MaxHeapNode::MaxHeapNode(string _month, int _year, string _artist,
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

void MaxHeapNode::copyData(MaxHeapNode *val) {
  month = val->month;
  year = val->year;
  artist = val->artist;
  title = val->title;
  recordLabel = val->recordLabel;
  weeksAtNumberOne = val->weeksAtNumberOne;
  key = title;
}

string MaxHeapNode::getRecord() {
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

int MaxHeapNode::max_depth() {
  int left_depth = left ? left->max_depth() : 0;
  int right_depth = right ? right->max_depth() : 0;
  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int MaxHeapNode::count() {
  return 1 + (left ? left->count() : 0) + (right ? right->count() : 0);
}

void MaxHeapNode::setLeft(MaxHeapNode *ptr) {
  left = ptr;
  if (ptr)
    ptr->parent = this;
}

void MaxHeapNode::setRight(MaxHeapNode *ptr) {
  right = ptr;
  if (ptr)
    ptr->parent = this;
}

MaxHeap::MaxHeap() {
  root = last = NULL;
  size = 0;
}

void MaxHeap::heapifyUp(MaxHeapNode *node) {
  while (node->parent && node->getData() > node->parent->getData()) {
    swapNodes(node, node->parent);
    node = node->parent;
  }
}

void MaxHeap::heapifyDown(MaxHeapNode *node) {
  while (node) {
    MaxHeapNode *swapNode = node;

    if (node->left && node->left->getData() > swapNode->getData())
      swapNode = node->left;
    if (node->right && node->right->getData() > swapNode->getData())
      swapNode = node->right;

    if (swapNode == node)
      break;

    swapNodes(node, swapNode);
    node = swapNode;
  }
}

void MaxHeap::swapNodes(MaxHeapNode *a, MaxHeapNode *b) {
  if (!a || !b)
    return;

  MaxHeapNode temp;
  temp.copyData(a);
  a->copyData(b);
  b->copyData(&temp);
}

void MaxHeap::insert(MaxHeapNode *node) {
  if (!root) {
    root = last = node;
    size = 1;
    return;
  }

  MaxHeapNode *parent = getParentOfNewNode();
  if (!parent->left) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
  last = node;
  size++;

  heapifyUp(node);
}
MaxHeapNode *MaxHeap::getParentOfNewNode() {
  if (size == 0)
    return NULL;

  int mask = 1 << ((int)log2(size + 1) - 1);
  MaxHeapNode *current = root;

  while (mask > 1) {
    current = (size + 1) & mask ? current->right : current->left;
    mask >>= 1;
  }
  return current;
}
void MaxHeap::remove(string value) {
  MaxHeapNode *node = find(value);
  if (!node)
    return;

  node->copyData(last);

  MaxHeapNode *lastParent = last->parent;
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

void MaxHeap::updateLastNode() {
  if (size == 0) {
    last = NULL;
    return;
  }

  int mask = 1 << ((int)log2(size)) - 1;
  MaxHeapNode *current = root;

  while (mask > 0) {
    current = size & mask ? current->right : current->left;
    mask >>= 1;
  }

  last = current;
}

MaxHeapNode *MaxHeap::find(string value) {
  return findNodeByValue(root, value);
}

MaxHeapNode *MaxHeap::findNodeByValue(MaxHeapNode *node, string value) {
  if (!node)
    return NULL;
  if (node->getData() == value)
    return node;

  MaxHeapNode *found = findNodeByValue(node->left, value);
  if (found)
    return found;

  return findNodeByValue(node->right, value);
}

string MaxHeap::display() { return displayHelper(root); }

string MaxHeap::displayHelper(MaxHeapNode *node) {
  string out = "";
  if (node == nullptr)
    return out;

  queue<MaxHeapNode *> q;
  q.push(node); // Start with the root node

  while (!q.empty()) {
    MaxHeapNode *currentNode = q.front();
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

#endif /* MAXHEAP_H */
