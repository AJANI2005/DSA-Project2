//
//  AVLTree.cpp
//  AVL
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.
//
//
//  The tree can be drawn from two separate functions:
//      (1) Draw(Tree) - Individual nodes are connected to the edges;
//      (2) StrDraw(Tree) - A string with all the edges connected.
//


#include <iostream>

#include<sstream>
#include<string>
#include<vector>

using namespace std;

#include "AVLTree.h"
#include "VisualizeAVL.h"



int main()
{
	
	AVL* avl = new AVL();

    
    cout <<"\nInserting: 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18\n\n";
    avl->insert(1);
    cout <<"\nDisplaying AVL Tree After Inserting: 1:\n\n";
    Draw(avl);
    
    avl->insert(2);
    cout <<"\nDisplaying AVL Tree After Inserting: 2:\n\n";
    Draw(avl);
    
    avl->insert(3);
    cout <<"\nDisplaying AVL Tree After Inserting: 3:\n\n";
    Draw(avl);
    
    avl->insert(4);
    cout <<"\nDisplaying AVL Tree After Inserting: 4:\n\n";
    Draw(avl);
    
    avl->insert(5);
    cout <<"\nDisplaying AVL Tree After Inserting: 5:\n\n";
    Draw(avl);
    
    avl->insert(6);
    cout <<"\nDisplaying AVL Tree After Inserting: 6:\n\n";
    Draw(avl);
    
    avl->insert(7);
    cout <<"\nDisplaying AVL Tree After Inserting: 7:\n\n";
    Draw(avl);
    
    avl->insert(8);
    cout <<"\nDisplaying AVL Tree After Inserting: 8:\n\n";
    Draw(avl);

    avl->insert(9);
    cout <<"\nDisplaying AVL Tree After Inserting: 9:\n\n";
    Draw(avl);
    
    avl->insert(10);
    cout <<"\nDisplaying AVL Tree After Inserting: 10:\n\n";
    Draw(avl);
    
    avl->insert(11);
    cout <<"\nDisplaying AVL Tree After Inserting: 11:\n\n";
    Draw(avl);
    
    avl->insert(12);
    cout <<"\nDisplaying AVL Tree After Inserting: 12:\n\n";
    Draw(avl);
    
    avl->insert(13);
    cout <<"\nDisplaying AVL Tree After Inserting: 13:\n\n";
    Draw(avl);
    
    avl->insert(14);
    cout <<"\nDisplaying AVL Tree After Inserting: 14:\n\n";
    Draw(avl);
    
    avl->insert(15);
    cout <<"\nDisplaying AVL Tree After Inserting: 15:\n\n";
    Draw(avl);
    
    avl->insert(16);
    cout <<"\nDisplaying AVL Tree After Inserting: 16:\n\n";
    Draw(avl);
    
    avl->insert(17);
    cout <<"\nDisplaying AVL Tree After Inserting: 17:\n\n";
    Draw(avl);
    
    avl->insert(18);
    cout <<"\nDisplaying AVL Tree After Inserting: 18:\n\n";
    Draw(avl);
   
    
    avl->remove(8);
    cout <<"\n\nDisplaying AVL Tree After REMOVING: 8:\n\n";
    Draw(avl);

    
	return 0;
}
