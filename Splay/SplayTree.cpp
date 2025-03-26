//
//  SplayTree.cpp
//  Splay
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.
//
//  The tree can be drawn from two separate functions:
//      (1) Draw(Tree) - Individual nodes are connected to the edges;
//      (2) StrDraw(Tree) - A string with all the edges connected.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "SplayTree.h"
#include "VisualizeSplayTree.h"



int main()
    {
        SplayTree* splay = new SplayTree();

//    splay->Insert(5);
//    splay->Insert(7);
//    splay->Insert(2);
//    splay->Insert(3);
//    splay->Insert(6);
//    splay->Insert(1);
//    splay->Insert(8);
//    splay->Insert(9);
//    splay->Insert(4);
//
//        Draw(splay);
//
//
//
//
//        cout << "Splay Inorder: \n" << splay->InOrder();
//        cout << "\nSplay Preorder: \n" << splay->PreOrder();
//        cout << "\nSplay Postorder: \n" << splay->PostOrder();
        
    cout <<"\n\t Inserting: 1, 6 , 3, 8, 4, 2, 9\n\n";

        splay->Insert(1);
        cout <<"\nDisplaying Splay Tree After Inserting: 1:\n\n";
        Draw(splay);
        
        splay->Insert(6);
        cout <<"\nDisplaying Splay Tree After Inserting: 6:\n\n";
        Draw(splay);

        splay->Insert(3);
        cout <<"\nDisplaying Splay Tree After Inserting: 3:\n\n";
        Draw(splay);
        
        splay->Insert(8);
        cout <<"\nDisplaying Splay Tree After Inserting: 8:\n\n";
        Draw(splay);
        
        splay->Insert(4);
        cout <<"\nDisplaying Splay Tree After Inserting: 4:\n\n";
        Draw(splay);
        
        splay->Insert(2);
        cout <<"\nDisplaying Splay Tree After Inserting: 2:\n\n";
        Draw(splay);
        
        splay->Insert(9);
        cout <<"\nDisplaying Splay Tree After Inserting: 9:\n\n";
        Draw(splay);
        

        return 0;
    }
