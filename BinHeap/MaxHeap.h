//
//  MaxHeap.h
//  Binary Heap Tree
//
//  Created by John Charlery on 21/01/2025.
//
//  Program to create a Maximum Binary Heap (MaxHeap), using tree-structured
//  pointers, without using vectors, queues or arrays.
//
//  This code is a mirror image of the MinHeap.h code
//
//========================================================================


#ifndef MaxHeap_h
#define MaxHeap_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

#include "Node.h"


//========================================================================
//====================== MaxHeap Class ===================================
//========================================================================

class MaxHeap
    {
        private:
            Node* insertHelper(Node*, Node*);
            int   number;                     // keep count of number of nodes in tree
            void  setParents(Node*);
            Node* findLastNode();
            void  heapifyDown(Node*);
            void  heapifyUp(Node*);
            Node* findNode(Node*, int);
        
        public:
            Node* root;

            MaxHeap()       {root = 0; number = 0;}
            Node* getRoot() { return root;}

            void  insert(int val){root = insertHelper(root, new Node(val)); number++;}
            void  deleteElement(int);
            int   get_max_depth() const { return root ? root->max_depth() : 0; }
            int   getLastNode(){return findLastNode()->data;}
  };




//------------------------------------------------------------------------
//      Function to delete a specific node from the tree
//------------------------------------------------------------------------
void MaxHeap::deleteElement(int value)
    {
        Node* targetNode = findNode(root, value);
        
        if (!targetNode) return;                // value is not found!

        // Replace target data with the last element's data
        Node* lastNode = findLastNode();
        
        cout << "\n\nTarget Node for Deletion = " << targetNode->data << "; \t Last Node = "
             << lastNode->data << "\n\n";
            
        targetNode->data = lastNode->data;  // Replace with last node's data


        // Remove last node from the heap
        if (lastNode->parent->left == lastNode)
            lastNode->parent->left = nullptr;
        else
            lastNode->parent->right = nullptr;
        
        
        // Get rid of the last node
        lastNode = nullptr;

        // Reduce the number of nodes
        number--;
        
        // Restore heap property from the deleted node's position
        heapifyDown(targetNode);
    }






//------------------------------------------------------------------------
//      Helper function to find the address of the last node in the heap
//------------------------------------------------------------------------
Node* MaxHeap::findLastNode()
    {
        int level = log2(number);               // Determine level of last node
        int position = number - (1 << level);   // Get node's Position within last level

        Node* last = root;
        for (int i = level; i > 0; --i)
            {
                if (position & (1 << (i - 1)))
                    last = last->right;
                else
                    last = last->left;
            }
        return last;
    }






//------------------------------------------------------------------------
//      Helper function to maintain the heap property by "heapifying down"
//------------------------------------------------------------------------
void MaxHeap::heapifyDown(Node* node)
    {
        if (!node) return;

        Node* largest = node;
        if (node->left && node->left->data > largest->data)
            largest = node->left;
        if (node->right && node->right->data > largest->data)
            largest = node->right;

        if (largest != node)
            {
                swap(node->data, largest->data);
                heapifyDown(largest);
            }
    }






//------------------------------------------------------------------------
//      Helper function to maintain the heap property by "heapifying up"
//------------------------------------------------------------------------
void MaxHeap::heapifyUp(Node* node)
    {
        while (node->parent && node->data > node->parent->data)
            {
                swap(node->data, node->parent->data);
                node = node->parent;
            }
    }






//------------------------------------------------------------------------
//      Helper function to get the address of a given node in the heap
//------------------------------------------------------------------------
Node* MaxHeap::findNode(Node* node, int value)
    {
        if (node == nullptr)
            return nullptr;
        if (node->data == value) return node;

        Node* foundNode = findNode(node->left, value);
        if (foundNode)
            return foundNode;

        return findNode(node->right, value);
    }






//------------------------------------------------------------------------
//      Helper function to establish the parent of a given node
//------------------------------------------------------------------------
void MaxHeap::setParents(Node* ptr)
    {
        if (ptr == NULL)
            return;
        else
            {
                if (ptr->left != NULL)
                    {
                        ptr->left->parent = ptr;
                        setParents(ptr->left);
                    }
                if (ptr->right != NULL)
                    {
                        ptr->right->parent = ptr;
                        setParents(ptr->right);
                    }
            }

    }






//------------------------------------------------------------------------
//      Helper function to insert a node into the heap recursively
//------------------------------------------------------------------------
Node* MaxHeap::insertHelper(Node* ptr, Node* node)
    {
        if(ptr == NULL)
            {
                ptr = node;
                return ptr;
            }

        else      // First... establish completeness...
            {
                if (balance(ptr) == 0 && check(ptr->right))         // insert in the right sub-tree
                        ptr->right = insertHelper(ptr->right,node);
                else if (balance(ptr) == 0)                         // insert in the left sub-tree
                        ptr->left = insertHelper(ptr->left,node);
                else if (balance(ptr) == 1 && check(ptr->left))     // insert in the left sub-tree
                        ptr->left = insertHelper(ptr->left,node);
                else if (balance(ptr) == 1)
                        ptr->right = insertHelper(ptr->right,node); // insert in right sub-tree
            }

        setParents(root);       // Make sure all nodes have their correct parent.
        heapifyUp(node);        // Then... re-establish heapness...
    
        return ptr;
    }



#endif /* MaxHeap_h */
