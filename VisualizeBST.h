//
//  VisualizeAllTree.h
//  DrawTree
//
//  Created by Dr. John Charlery on 10/3/2020.
//  Copyright (c) 2020 University of the West Indies. All rights reserved.
//

#ifndef VISUALIZETREE_H
#define VISUALIZETREE_H

#include <stdio.h>
#include <string.h>

using namespace std;

#include "BSTree.h"

// #include "AVLTree.h"
// #include "RBTree.h"

#define MAX_HEIGHT 1000
int leftProfile[MAX_HEIGHT];
int rightProfile[MAX_HEIGHT];

#define INFINITE (1 << 20)

int gap = 3;    // Adjust gap between left and right nodes
int print_next; // x coordinate of the next value to be printed

class AsciiNode {
public:
  AsciiNode *left;
  AsciiNode *right;

  string color;
  int edge_length; // length of the edge from this node to its children
  int height;
  int lablen;
  int parent_dir; //-1=I am left, 0=I am root, 1=right
  string label;   // max supported unit32 in dec, 10 digits max
};

int MIN(int X, int Y) { return ((X) < (Y)) ? (X) : (Y); }

int MAX(int X, int Y) { return ((X) > (Y)) ? (X) : (Y); }

AsciiNode *build_ascii_Node_recursive(BSTNode *ptr) {
  AsciiNode *node = new AsciiNode;

  if (ptr == NULL)
    return NULL;

  node->left = build_ascii_Node_recursive(ptr->getLeft());
  node->right = build_ascii_Node_recursive(ptr->getRight());
  node->color = "";

  if (node->left != NULL) {
    node->left->parent_dir = -1;
  }

  if (node->right != NULL) {
    node->right->parent_dir = 1;
  }

  //        sprintf(node->label, "%d", ptr->getData());
  node->label = ptr->getData();
  node->lablen = node->label.length();

  return node;
}

// Copy the Node into the ascii node structre
AsciiNode *build_ascii_Node(BSTNode *ptr) {
  AsciiNode *node;
  if (ptr == NULL)
    return NULL;

  node = build_ascii_Node_recursive(ptr);
  node->parent_dir = 0;
  return node;
}

// Free all the nodes of the given Node
void freeUpNode(AsciiNode *node) {
  if (node == NULL)
    return;

  freeUpNode(node->left);
  freeUpNode(node->right);
  delete node;
}

// AsciiNode* build_ascii_Node_recursive(AVLNode* ptr)
//     {
//         AsciiNode* node = new AsciiNode;
//
//         if (ptr == NULL) return NULL;
//
//         node->left = build_ascii_Node_recursive(ptr->left);
//         node->right = build_ascii_Node_recursive(ptr->right);
//         node->color = "";
//
//         if (node->left != NULL)
//             {
//                 node->left->parent_dir = -1;
//             }
//
//         if (node->right != NULL)
//             {
//                 node->right->parent_dir = 1;
//             }
//
//         sprintf(node->label, "%d", ptr->getData());
//         node->lablen = (int) strlen(node->label);
//
//         return node;
//     }
//
//
//
//
//     //Copy the Node into the ascii node structre
// AsciiNode * build_ascii_Node(AVLNode* ptr)
//     {
//         AsciiNode *node;
//         if (ptr == NULL) return NULL;
//
//         node = build_ascii_Node_recursive(ptr);
//         node->parent_dir = 0;
//         return node;
//     }
//
//
//
//
//
//
// AsciiNode* build_ascii_Node_recursive(RBTNode* ptr)
//     {
//         AsciiNode* node = new AsciiNode;
//
//         if (ptr == NULL) return NULL;
//
//         node->left = build_ascii_Node_recursive(ptr->left);
//         node->right = build_ascii_Node_recursive(ptr->right);
//         if (ptr->getColor() == "RED")
//             node->color = "R";
//         else
//             node->color = "";
//
//         if (node->left != NULL)
//             {
//                 node->left->parent_dir = -1;
//             }
//
//         if (node->right != NULL)
//             {
//                 node->right->parent_dir = 1;
//             }
//
//         sprintf(node->label, "%d", ptr->getData());
//         node->lablen = (int) strlen(node->label);
//
//         return node;
//     }
//
//
//
//
//     //Copy the Node into the ascii node structre
// AsciiNode * build_ascii_Node(RBTNode* ptr)
//     {
//         AsciiNode *node;
//         if (ptr == NULL) return NULL;
//
//         node = build_ascii_Node_recursive(ptr);
//         node->parent_dir = 0;
//         return node;
//     }
//
//
//
//
//
// AsciiNode* build_ascii_Node_recursive(SplayNode* ptr)
//     {
//         AsciiNode* node = new AsciiNode;
//
//         if (ptr == NULL) return NULL;
//
//         node->left = build_ascii_Node_recursive(ptr->left);
//         node->right = build_ascii_Node_recursive(ptr->right);
//         node->color = "";
//
//         if (node->left != NULL)
//             {
//                 node->left->parent_dir = -1;
//             }
//
//         if (node->right != NULL)
//             {
//                 node->right->parent_dir = 1;
//             }
//
//         sprintf(node->label, "%d", ptr->getData());
//         node->lablen = (int) strlen(node->label);
//
//         return node;
//     }
//
//
//
//
//     //Copy the Node into the ascii node structre
// AsciiNode * build_ascii_Node(SplayNode* ptr)
//     {
//         AsciiNode *node;
//         if (ptr == NULL) return NULL;
//
//         node = build_ascii_Node_recursive(ptr);
//         node->parent_dir = 0;
//         return node;
//     }
//

// The following function fills in the leftProfile array for the given Node.
// It assumes that the center of the label of the root of this Node
// is located at a position (x,y).  It assumes that the edge_length
// fields have been computed for this Node.
void computeLeftProfile(AsciiNode *node, int x, int y) {
  int i, isleft;

  if (node == NULL)
    return;

  isleft = (node->parent_dir == -1);
  leftProfile[y] = MIN(leftProfile[y], x - ((node->lablen - isleft) / 2));

  if (node->left != NULL) {
    for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
      leftProfile[y + i] = MIN(leftProfile[y + i], x - i);
    }
  }
  computeLeftProfile(node->left, x - node->edge_length - 1,
                     y + node->edge_length + 1);
  computeLeftProfile(node->right, x + node->edge_length + 1,
                     y + node->edge_length + 1);
}

// The following function fills in the rightProfile array for the given Node.
// It assumes that the center of the label of the root of this Node
// is located at a position (x,y).  It assumes that the edge_length
// fields have been computed for this Node.
void computeRightProfile(AsciiNode *node, int x, int y) {
  int i, notleft;
  if (node == NULL)
    return;

  notleft = (node->parent_dir != -1);
  rightProfile[y] = MAX(rightProfile[y], x + ((node->lablen - notleft) / 2));

  if (node->right != NULL) {
    for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
      rightProfile[y + i] = MAX(rightProfile[y + i], x + i);
    }
  }
  computeRightProfile(node->left, x - node->edge_length - 1,
                      y + node->edge_length + 1);
  computeRightProfile(node->right, x + node->edge_length + 1,
                      y + node->edge_length + 1);
}

// This function fills in the edge_length and height fields of the specified
// Node
void computeEdgeLengths(AsciiNode *node) {
  int h, hmin, i, delta;
  if (node == NULL)
    return;

  computeEdgeLengths(node->left);
  computeEdgeLengths(node->right);

  // first fill in the edge_length of node
  if (node->right == NULL && node->left == NULL) {
    node->edge_length = 0;
  } else {
    if (node->left != NULL) {
      for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
        rightProfile[i] = -INFINITE;
      }
      computeRightProfile(node->left, 0, 0);
      hmin = node->left->height;
    } else {
      hmin = 0;
    }
    if (node->right != NULL) {
      for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
        leftProfile[i] = INFINITE;
      }
      computeLeftProfile(node->right, 0, 0);
      hmin = MIN(node->right->height, hmin);
    } else {
      hmin = 0;
    }

    delta = 4;

    for (i = 0; i < hmin; i++) {
      delta = MAX(delta, gap + 1 + rightProfile[i] - leftProfile[i]);
    }

    // If the node has two children of height 1, then we allow the
    // two leaves to be within 1, instead of 2
    if (((node->left != NULL && node->left->height == 1) ||
         (node->right != NULL && node->right->height == 1)) &&
        delta > 4) {
      delta--;
    }

    node->edge_length = ((delta + 1) / 2) - 1;
  }

  // now fill in the height of node
  h = 1;

  if (node->left != NULL) {
    h = MAX(node->left->height + node->edge_length + 1, h);
  }

  if (node->right != NULL) {
    h = MAX(node->right->height + node->edge_length + 1, h);
  }

  node->height = h;
}

// This function prints the given level of the given Node, assuming
// that the node has the given x cordinate.

void displayLevel(AsciiNode *node, int x, int level) {
  int i, isleft;

  if (node == NULL)
    return;
  isleft = (node->parent_dir == -1);
  if (level == 0) {
    for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
      cout << " ";
    }
    print_next += i;
    cout << node->label;
    print_next += node->lablen;
  } else if (node->edge_length >= level) {
    if (node->left != NULL) {
      for (i = 0; i < (x - print_next - (level)); i++) {
        cout << " ";
      }
      print_next += i;
      cout << "/";
      print_next++;
    }
    if (node->right != NULL) {
      for (i = 0; i < (x - print_next + (level)); i++) {
        cout << " ";
      }
      print_next += i;
      cout << "\\";
      print_next++;
    }
  } else {
    displayLevel(node->left, x - node->edge_length - 1,
                 level - node->edge_length - 1);
    displayLevel(node->right, x + node->edge_length + 1,
                 level - node->edge_length - 1);
  }
}

string displayLevelStr(AsciiNode *node, int x, int level) {
  int i, isleft;
  string str = "";

  if (node == NULL)
    return str;

  isleft = (node->parent_dir == -1);
  if (level == 0) {
    for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
      str.append(" ");
    }
    print_next += i;
    str.append(node->label);
    str.append(node->color);
    print_next += node->lablen;
  } else if (node->edge_length >= level) {
    if (node->left != NULL) {
      for (i = 0; i < (x - print_next - (level)); i++) {
        str.append(" ");
      }
      print_next += i;
      str.append("/");
      print_next++;
    }
    if (node->right != NULL) {
      for (i = 0; i < (x - print_next + (level)); i++) {
        str.append(" ");
      }
      print_next += i;
      str.append("\\");
      print_next++;
    }
  } else {
    str.append(displayLevelStr(node->left, x - node->edge_length - 1,
                               level - node->edge_length - 1));
    str.append(displayLevelStr(node->right, x + node->edge_length + 1,
                               level - node->edge_length - 1));
  }
  return str;
}

template <class Tree>

// prints ascii Node for given Node structure
string displayTree(Tree *ptr) {
  AsciiNode *proot;
  int xmin, i;
  string str = "\t";

  if (ptr->getRoot() == NULL)
    return str;

  proot = build_ascii_Node(ptr->getRoot());
  computeEdgeLengths(proot);

  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
    leftProfile[i] = INFINITE;
  }

  computeLeftProfile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
    xmin = MIN(xmin, leftProfile[i]);
  }

  for (i = 0; i < proot->height; i++) {
    print_next = 0;

    str.append(displayLevelStr(proot, -xmin, i));
    str.append("\n\t");
  }

  if (proot->height >= MAX_HEIGHT) {
    cout << "(This Node is taller than " << MAX_HEIGHT
         << "and may be drawn incorrectly.)\n";
  }

  freeUpNode(proot);
  return str;
}

#endif
