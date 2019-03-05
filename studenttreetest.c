#include <stdio.h>
#include "binarytree.h"

struct TreeNode* makeTestTree(int n,int lim, int count)
{
  struct TreeNode* root = NULL;
  if(n > 1 && count <= lim)
  {
    root = createTreeNode(count);
    root -> left = makeTestTree(n-1, lim, 2*count);
    root -> right = makeTestTree(n-2, lim, 2*count+1);
  }
  return root;
}

int main()
{
  struct TreeNode* tree = makeTestTree(2, 1, 1);
  printf("one node tree: ");
  printTree(tree);
  dfs(tree);
  freeTree(tree);
  tree = NULL;
  
  tree = makeTestTree(1, 1, 1);
  printf("empty tree: ");
  printTree(tree);
  dfs(tree);
  freeTree(tree);
  tree = NULL;

  tree = makeTestTree(300, 128, 1);
  printf("big tree: ");
  printTree(tree);
  dfs(tree);
  freeTree(tree);
  tree = NULL;
  return 0;
}
