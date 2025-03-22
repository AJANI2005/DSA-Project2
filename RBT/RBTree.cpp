//
//  RBTree.cpp
//  RBT
//
//  Created by Dr. John Charlery on 03/15/2025.
//  Copyright (c) 2025 University of the West Indies. All rights reserved.
//
//  The tree can be drawn from two separate functions:
//      (1) Draw(Tree) - Individual nodes are connected to the edges;
//      (2) StrDraw(Tree) - A string with all the edges connected.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "RBTree.h"
#include "VisualizeRBT.h"

int main() {

  RBT *rbt = new RBT();

  cout << "\n\t Inserting: 5, 8 ,4, 2, 9, 18, 7, 6, 14\n\n";

  rbt->insert(5);
  cout << "\nDisplaying Red-Black Tree After Inserting: 5:\n\n";
  Draw(rbt);

  rbt->insert(8);
  cout << "\nDisplaying Red-Black Tree After Inserting: 8:\n\n";
  Draw(rbt);

  rbt->insert(4);
  cout << "\nDisplaying Red-Black Tree After Inserting: 4:\n\n";
  Draw(rbt);

  rbt->insert(2);
  cout << "\nDisplaying Red-Black Tree After Inserting: 2:\n\n";
  Draw(rbt);

  rbt->insert(9);
  cout << "\nDisplaying Red-Black Tree After Inserting: 9:\n\n";
  Draw(rbt);

  rbt->insert(18);
  cout << "\nDisplaying Red-Black Tree After Inserting: 18:\n\n";
  Draw(rbt);

  rbt->insert(7);
  cout << "\nDisplaying Red-Black Tree After Inserting: 7:\n\n";
  Draw(rbt);

  rbt->insert(6);
  cout << "\nDisplaying Red-Black Tree After Inserting: 6:\n\n";
  Draw(rbt);

  rbt->insert(14);
  cout << "\nDisplaying Red-Black Tree After Inserting: 14:\n\n";
  Draw(rbt);

  cout << "\n\n";

  return 0;
}
