#include "BinHeap.h"
#include "VisualizeHeap.h"

int main() {
  MinHeap *tree1 = new MinHeap();
  MaxHeap *tree2 = new MaxHeap();
  HeapNode *node1 =
      new HeapNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  HeapNode *node2 =
      new HeapNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  HeapNode *node3 =
      new HeapNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  HeapNode *node4 =
      new HeapNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  HeapNode *node5 =
      new HeapNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);

  tree1->insert(node1);
  tree1->insert(node2);
  tree1->insert(node3);
  tree1->insert(node4);
  tree1->insert(node5);

  HeapNode *node6 =
      new HeapNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  HeapNode *node7 =
      new HeapNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  HeapNode *node8 =
      new HeapNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  HeapNode *node9 =
      new HeapNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  HeapNode *node10 =
      new HeapNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);
  tree2->insert(node6);
  tree2->insert(node7);
  tree2->insert(node8);
  tree2->insert(node9);
  tree2->insert(node10);

  cout << "Tree 1 (Min Heap)" << endl;
  cout << tree1->display() << endl;
  Draw(tree1);

  cout << "\n\n\n";

  cout << "Tree 2 (Max Heap)" << endl;
  cout << tree2->display() << endl;
  Draw(tree2);

  return 0;
}
