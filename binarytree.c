/*********************
 * Elijah Johnson
 * Binary tree implementation for binarytree.h
 * 11/18/2018
 * Lab Section 001
 */

#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"
#include "linkedlist.h"

/*****************
 * Creates a new tree node to be put into a tree
 * @param data the data to be put in the node
 * @return NULL if malloc fails or the new node that was created
 */
struct TreeNode* createTreeNode(int data)
{
  struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
  if (!newNode)
  {
    return NULL;
  }
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/**********************
 * Helper function to print out a binary tree
 * @param *root a pointer to the root of the tree
 */
void printTreeHelper(struct TreeNode* root)
{
  /*Check if root exsits and then print it out in order
   * left then root then right
   */
  if (root)
  {
    printTreeHelper(root->left);
    printf("%d ", root->data);
    printTreeHelper(root->right);
  }
}

/****************
 * Prints out a binary tree recursivley
 * @param *root the binary tree to be printed
 */
void printTree(struct TreeNode* root)
{
  printTreeHelper(root);
  printf("\n");
}


/********************
 * Frees a binary tree
 * @param *root the binary tree to free
 */
void freeTree(struct TreeNode* root)
{
  /*Check if root exsits then free
   * left and right recursivley then root
   */
  if (root)
  {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}

/************
 * Helper function for depth first search of binary tree
 * @param *root the tree to be looked through
 * @param **stack the stack to be filled as it is searched
 */
void dfsHelper(struct TreeNode *root, struct ListNode **stack)
{
  if (root)
  {
    /*Push the data into the stack and then check
     * right subtree and then left
     */
    *stack = pushStack(*stack, root->data);
    dfsHelper(root->right, stack);
    dfsHelper(root->left, stack);
  }
}

/***********************
 * Preform depth first search on a tree
 * @param *root the root node to preform the search on
 */
void dfs(struct TreeNode* root)
{
  /*Stack to hold data */
  struct ListNode *stack = NULL;
  int count = 0;

  /*If root isnt null call recursive helper*/
  if (root)
  {
    dfsHelper(root, &stack);
    /*Reverse the stack so it prints out in correct order*/
    reverseList(&stack);
    if (stack)
    {
      while (stack->next != stack)
      {
        /*Print out the data and the count */
        printf("%d: %d\n", ++count, popStack(&stack));
      }

      printf("%d: %d\n", ++count, popStack(&stack));
    }
  }
}
