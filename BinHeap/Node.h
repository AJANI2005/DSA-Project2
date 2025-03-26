//
//  Node.h
//  BinaryHeap
//
//  Created by John Charlery on 20/01/2025.
//

#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

class Node
    {
        public:
            int data;
            Node *left, *right, *parent;

            Node(int data);
            Node(){parent = left = right = NULL;}
            ~Node();
            int  count();
            void print(const int indent, const char* note);
            int  getData()   { return data;}
            Node* getLeft() {return left;}
            Node* getRight(){return right;}
            int max_depth() const;
        
            void setData(int val)   { data = val;}
            void setLeft(Node* ptr) {left = ptr;}
            void setRight(Node* ptr){right = ptr;}
     };

//------------------------------------------------------------------------
// Prototype of functions which are needed in member functions of Node
//------------------------------------------------------------------------
int  height(Node*);
int  balance(Node*);
bool check(Node*);
void swapData(Node*);
//------------------------------------------------------------------------


Node::Node(int val)
    {
       data = val;
       parent = left = right = NULL;
    }

Node::~Node()
    {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
        if (parent != NULL) delete parent;
    }


int Node::max_depth() const
    {
        const int left_depth = left ? left->max_depth() : 0;
        const int right_depth = right ? right->max_depth() : 0;
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }


int Node::count()
    {
        int kount = 1;
        if (left != NULL) kount += left->count();
        if (right != NULL) kount += right->count();
    
        return kount;
    }





void swapData(Node* node)
    {
        int temp = node->data;
        node->data = node->parent->data;
        node->parent->data = temp;
    }




int height(Node *ptr)
    {
        if(ptr == NULL)
            return 0;
        else
        {
            int leftHeight = height(ptr->left) + 1;
            int rightHeight = height(ptr->right) + 1;

            return (leftHeight > rightHeight) ? leftHeight : rightHeight; //returns maximum height
        }
    }




// Method to get the balance factor of a given node
// [Balance Factor = Height of Left Sub-Tree - Height ofRight Sub-Tree]
int balance(Node* ptr)
    {
        if(ptr == NULL)
            return 0;
    
        int lheight = height(ptr->left)+1;
        int rheight = height(ptr->right)+1;

        return (lheight - rheight);
    }





bool check(Node* ptr)
    {
        //traversing the nodes of the subtree to check any node with balance != 0
        if(ptr == NULL)
            return false;
        bool x = check(ptr->left);
    
        if(balance(ptr))
            return true;
    
        bool y = check(ptr->right);
        return x||y;    //If any node present with balance factor != 0
    }


#endif /* Node_h */
