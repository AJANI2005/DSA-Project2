#include "MaxHeap.h"
#include "MinHeap.h"
#include "VisualizeHeap.h"

int main() {
  MinHeap *tree1 = new MinHeap();
  MaxHeap *tree2 = new MaxHeap();
  MinHeapNode *node1 =
      new MinHeapNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  MinHeapNode *node2 =
      new MinHeapNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  MinHeapNode *node3 =
      new MinHeapNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  MinHeapNode *node4 =
      new MinHeapNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  MinHeapNode *node5 =
      new MinHeapNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);

  tree1->insert(node1);
  tree1->insert(node2);
  tree1->insert(node3);
  tree1->insert(node4);
  tree1->insert(node5);

  MaxHeapNode *node6 =
      new MaxHeapNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  MaxHeapNode *node7 =
      new MaxHeapNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  MaxHeapNode *node8 =
      new MaxHeapNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  MaxHeapNode *node9 =
      new MaxHeapNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  MaxHeapNode *node10 =
      new MaxHeapNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);
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
