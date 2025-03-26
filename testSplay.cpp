#include "SplayTree.h"
#include "VisualizeSplayTree.h"

int main() {
  SplayTree *tree = new SplayTree();
  SplayNode *node1 =
      new SplayNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  SplayNode *node2 =
      new SplayNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  SplayNode *node3 =
      new SplayNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  SplayNode *node4 =
      new SplayNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  SplayNode *node5 =
      new SplayNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);

  tree->insert(node1);
  tree->insert(node3);
  tree->insert(node2);
  tree->insert(node5);
  tree->insert(node4);

  Draw(tree);
  cout << "Inorder" << endl;
  cout << tree->InOrder() << endl;

  cout << "Preorder" << endl;
  cout << tree->PreOrder() << endl;

  cout << "Postorder" << endl;
  cout << tree->PostOrder() << endl;

  delete tree;
  return 0;
}
