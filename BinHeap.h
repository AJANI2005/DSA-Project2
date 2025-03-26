

#ifndef BINHEAP_H
#define BINHEAP_H

#include <cmath>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class HeapNode {
public:
  // data
  string month;
  int year;
  string artist;
  string title;
  string recordLabel;
  int weeksAtNumberOne;

  HeapNode *left, *right, *parent;
  string key;

  // constructor
  HeapNode(string _month, int _year, string _artist, string _title,
           string _recordLbl, int _weeksAtNumberOne);
  HeapNode() { left = right = parent = NULL; };

  // accessor functions
  int count();
  string getData() { return key; }
  HeapNode *getLeft() { return left; }
  HeapNode *getRight() { return right; }
  int max_depth();
  string getRecord();

  // mutator functions
  void copyData(HeapNode *val);
  void setLeft(HeapNode *ptr);
  void setRight(HeapNode *ptr);
};

class MinHeap {
private:
  HeapNode *root;
  HeapNode *last;
  int size;

  void heapifyUp(HeapNode *node);
  void heapifyDown(HeapNode *node);
  void swapNodes(HeapNode *a, HeapNode *b);
  HeapNode *findNodeByValue(HeapNode *node, string value);
  void updateLastNode();
  HeapNode *getParentOfNewNode();
  void setParents(HeapNode *node, HeapNode *parent = NULL);

public:
  MinHeap();

  HeapNode *getRoot() { return root; }
  string getLast() { return last ? last->getData() : ""; }
  int getSize() { return size; }
  int get_max_depth() { return root ? root->max_depth() : 0; }

  void insert(HeapNode *node);
  void remove(string value);
  HeapNode *find(string value);
  string display();
  string displayHelper(HeapNode *node);
};

class MaxHeap {
private:
  HeapNode *root;
  HeapNode *last;
  int size;

  void heapifyUp(HeapNode *node);
  void heapifyDown(HeapNode *node);
  void swapNodes(HeapNode *a, HeapNode *b);
  HeapNode *findNodeByValue(HeapNode *node, string value);
  void updateLastNode();
  HeapNode *getParentOfNewNode();
  void setParents(HeapNode *node, HeapNode *parent = NULL);

public:
  MaxHeap();

  HeapNode *getRoot() { return root; }
  string getLast() { return last ? last->getData() : ""; }
  int getSize() { return size; }
  int get_max_depth() { return root ? root->max_depth() : 0; }

  void insert(HeapNode *node);
  void remove(string value);
  HeapNode *find(string value);
  string display();
  string displayHelper(HeapNode *node);
};

// HeapNode Implementation
HeapNode::HeapNode(string _month, int _year, string _artist, string _title,
                   string _recordLbl, int _weeksAtNumberOne) {
  month = _month;
  year = _year;
  artist = _artist;
  title = _title;
  recordLabel = _recordLbl;
  weeksAtNumberOne = _weeksAtNumberOne;
  key = title;
  left = right = parent = NULL;
}

void HeapNode::copyData(HeapNode *val) {
  month = val->month;
  year = val->year;
  artist = val->artist;
  title = val->title;
  recordLabel = val->recordLabel;
  weeksAtNumberOne = val->weeksAtNumberOne;
  key = title;
}

string HeapNode::getRecord() {
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

int HeapNode::max_depth() {
  int left_depth = left ? left->max_depth() : 0;
  int right_depth = right ? right->max_depth() : 0;
  return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int HeapNode::count() {
  return 1 + (left ? left->count() : 0) + (right ? right->count() : 0);
}

void HeapNode::setLeft(HeapNode *ptr) {
  left = ptr;
  if (ptr)
    ptr->parent = this;
}

void HeapNode::setRight(HeapNode *ptr) {
  right = ptr;
  if (ptr)
    ptr->parent = this;
}

// MinHeap Implementation
MinHeap::MinHeap() {
  root = last = NULL;
  size = 0;
}

void MinHeap::setParents(HeapNode *node, HeapNode *parent) {
  if (!node)
    return;
  node->parent = parent;
  setParents(node->left, node);
  setParents(node->right, node);
}

void MinHeap::insert(HeapNode *node) {
  if (!root) {
    root = last = node;
    size = 1;
    return;
  }

  HeapNode *parent = getParentOfNewNode();
  if (!parent->left) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
  last = node;
  size++;

  heapifyUp(node);
}

HeapNode *MinHeap::getParentOfNewNode() {
  if (size == 0)
    return NULL;

  int mask = 1 << ((int)log2(size + 1) - 1);
  HeapNode *current = root;

  while (mask > 1) {
    current = (size + 1) & mask ? current->right : current->left;
    mask >>= 1;
  }
  return current;
}

void MinHeap::heapifyUp(HeapNode *node) {
  while (node->parent && node->getData() < node->parent->getData()) {
    swapNodes(node, node->parent);
    node = node->parent;
  }
}

void MinHeap::heapifyDown(HeapNode *node) {
  while (node) {
    HeapNode *swapNode = node;

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

void MinHeap::swapNodes(HeapNode *a, HeapNode *b) {
  if (!a || !b)
    return;

  HeapNode temp;
  temp.copyData(a);
  a->copyData(b);
  b->copyData(&temp);
}

void MinHeap::remove(string value) {
  HeapNode *node = find(value);
  if (!node)
    return;

  node->copyData(last);

  HeapNode *lastParent = last->parent;
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
  HeapNode *current = root;

  while (mask > 0) {
    current = size & mask ? current->right : current->left;
    mask >>= 1;
  }

  last = current;
}

HeapNode *MinHeap::find(string value) { return findNodeByValue(root, value); }

HeapNode *MinHeap::findNodeByValue(HeapNode *node, string value) {
  if (!node)
    return NULL;
  if (node->getData() == value)
    return node;

  HeapNode *found = findNodeByValue(node->left, value);
  if (found)
    return found;

  return findNodeByValue(node->right, value);
}

string MinHeap::display() { return displayHelper(root); }

string MinHeap::displayHelper(HeapNode *node) {
  string out = "";
  if (node == nullptr)
    return out;

  queue<HeapNode *> q;
  q.push(node); // Start with the root node

  while (!q.empty()) {
    HeapNode *currentNode = q.front();
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

MaxHeap::MaxHeap() {
  root = last = NULL;
  size = 0;
}

void MaxHeap::heapifyUp(HeapNode *node) {
  while (node->parent && node->getData() > node->parent->getData()) {
    swapNodes(node, node->parent);
    node = node->parent;
  }
}

void MaxHeap::heapifyDown(HeapNode *node) {
  while (node) {
    HeapNode *swapNode = node;

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

void MaxHeap::swapNodes(HeapNode *a, HeapNode *b) {
  if (!a || !b)
    return;

  HeapNode temp;
  temp.copyData(a);
  a->copyData(b);
  b->copyData(&temp);
}

void MaxHeap::insert(HeapNode *node) {
  if (!root) {
    root = last = node;
    size = 1;
    return;
  }

  HeapNode *parent = getParentOfNewNode();
  if (!parent->left) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
  last = node;
  size++;

  heapifyUp(node);
}
HeapNode *MaxHeap::getParentOfNewNode() {
  if (size == 0)
    return NULL;

  int mask = 1 << ((int)log2(size + 1) - 1);
  HeapNode *current = root;

  while (mask > 1) {
    current = (size + 1) & mask ? current->right : current->left;
    mask >>= 1;
  }
  return current;
}
void MaxHeap::remove(string value) {
  HeapNode *node = find(value);
  if (!node)
    return;

  node->copyData(last);

  HeapNode *lastParent = last->parent;
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
  HeapNode *current = root;

  while (mask > 0) {
    current = size & mask ? current->right : current->left;
    mask >>= 1;
  }

  last = current;
}

HeapNode *MaxHeap::find(string value) { return findNodeByValue(root, value); }

HeapNode *MaxHeap::findNodeByValue(HeapNode *node, string value) {
  if (!node)
    return NULL;
  if (node->getData() == value)
    return node;

  HeapNode *found = findNodeByValue(node->left, value);
  if (found)
    return found;

  return findNodeByValue(node->right, value);
}

string MaxHeap::display() { return displayHelper(root); }

string MaxHeap::displayHelper(HeapNode *node) {
  string out = "";
  if (node == nullptr)
    return out;

  queue<HeapNode *> q;
  q.push(node); // Start with the root node

  while (!q.empty()) {
    HeapNode *currentNode = q.front();
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

#endif /* BINHEAP_H */
