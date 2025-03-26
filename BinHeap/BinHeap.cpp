//
//  BinHeap.cpp
//  Binary Heap Tree
//
//  Created by John Charlery on 21/01/2025.
//
//  Program to create Minimum and Maximum Binary Heaps (MinHeap/MaxHeap),
//  which use tree-structured pointers, without using vectors, queues or
//  arrays.
//
//  The classes codes for the MinHeap and MaxHeap are mirror images of
//  each other.
//
//  The tree can be drawn from two separate functions:
//      (1) Draw(Tree) - Individual nodes are connected to the edges;
//      (2) StrDraw(Tree) - A string with all the edges connected.
//
//========================================================================


#include<iostream>
using namespace std;

#include "MinHeap.h"
#include "MaxHeap.h"
#include "VisualizeHeap.h"

int main(int argc, char const *argv[])
    {
        MinHeap* minheap = new MinHeap();
        MaxHeap* maxheap = new MaxHeap();

        minheap->insert(8);
        minheap->insert(5);
        minheap->insert(2);
        minheap->insert(6);
        minheap->insert(10);
        minheap->insert(9);
        minheap->insert(12);
        minheap->insert(7);
        minheap->insert(3);
        minheap->insert(1);
        minheap->insert(10);
        minheap->insert(9);
        minheap->insert(12);
        minheap->insert(7);
        minheap->insert(3);
        Draw(minheap);
    
    cout << "\nTree returning as a string:\n" << StrDraw(minheap) << "\n\n";

        minheap->deleteElement(1);
        Draw(minheap);
        minheap->deleteElement(3);
        Draw(minheap);
        minheap->deleteElement(7);
        Draw(minheap);
        minheap->deleteElement(6);
        Draw(minheap);

    
    
        maxheap->insert(8);
        maxheap->insert(5);
        maxheap->insert(2);
        maxheap->insert(6);
        maxheap->insert(10);
        maxheap->insert(9);
        maxheap->insert(12);
        maxheap->insert(7);
        maxheap->insert(3);
        maxheap->insert(1);
        maxheap->insert(10);
        maxheap->insert(9);
        maxheap->insert(12);
        maxheap->insert(7);
        maxheap->insert(3);
        Draw(maxheap);

        maxheap->deleteElement(12);
        Draw(maxheap);
        maxheap->deleteElement(10);
        Draw(maxheap);
        maxheap->deleteElement(8);
        Draw(maxheap);
        maxheap->deleteElement(6);
        Draw(maxheap);

        cout << "\nTree returning as a string:\n" << StrDraw(maxheap) << "\n\n";

        return 0;
    }
