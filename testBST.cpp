#include "BSTree.h"
#include "VisualizeBST.h"

int main() {
  BSTree *tree = new BSTree();
  BSTNode *node1 =
      new BSTNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  BSTNode *node2 =
      new BSTNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  BSTNode *node3 =
      new BSTNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  BSTNode *node4 =
      new BSTNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  BSTNode *node5 =
      new BSTNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);

  tree->insert(node1);
  tree->insert(node3);
  tree->insert(node2);
  tree->insert(node5);
  tree->insert(node4);

  cout << displayTree(tree) << endl;
  cout << "Inorder" << endl;
  cout << tree->inOrder() << endl;

  cout << "Preorder" << endl;
  cout << tree->preOrder() << endl;

  cout << "Postorder" << endl;
  cout << tree->postOrder() << endl;

  delete tree;
  return 0;
}
