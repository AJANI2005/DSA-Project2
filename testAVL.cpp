#include "AVLTree.h"
#include "VisualizeAVL.h"

int main() {
  AVLTree *tree = new AVLTree();
  AVLNode *node1 =
      new AVLNode("January", 2000, "John Doe", "Song 1", "Label 1", 10);
  AVLNode *node2 =
      new AVLNode("Feb", 2001, "Jane Smith", "Song 2", "Label 2", 5);
  AVLNode *node3 =
      new AVLNode("March", 2002, "Mike Johnson", "Song 3", "Label 3", 8);
  AVLNode *node4 =
      new AVLNode("April", 2003, "Sarah Brown", "Song 4", "Label 4", 15);
  AVLNode *node5 =
      new AVLNode("May", 2004, "David Wilson", "Song 5", "Label 5", 3);

  tree->insert(node1);
  tree->insert(node3);
  tree->insert(node2);
  tree->insert(node5);
  tree->insert(node4);

  Draw(tree);
  cout << "Inorder" << endl;
  cout << tree->inOrder() << endl;

  cout << "Preorder" << endl;
  cout << tree->preOrder() << endl;

  cout << "Postorder" << endl;
  cout << tree->postOrder() << endl;

  delete tree;
  return 0;
}
