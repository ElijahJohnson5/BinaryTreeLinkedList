/****************************
 * Elijah Johnson
 * Implementation of functions in linkedlist.h
 * Implements a double linked list, inserting and sorting
 * 
 * Lab Section 001
 * @date 11/08/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/*******************
 * Creates a new node with the data passed to it
 * @param data the data to be put in the node values can be 
 *  any int value
 * @return the newly created and allocated node needs to be
 *  freed at a later time
 */
struct ListNode* createNode(int data)
{
  /*Allocate space*/
  struct ListNode *newNode = malloc(sizeof(struct ListNode));
  if (!newNode) /*check if malloc works */
  {
    return NULL;
  }

  newNode->next = newNode;
  newNode->prev = newNode;
  newNode->data = data;

  return newNode;
}

/**********************
 * Inserts a node in the middle of the list after currentNode
 * @param *head a pointer to the head of the list
 * @param *currentNode a pointer to the node to insert the new
 *  node after
 * @param data the data to be put in the new node
 * @return the head pointer which does not get changed
 */
struct ListNode* insertMiddle(struct ListNode *head, 
                              struct ListNode* currentNode, int data, int before)
{
  struct ListNode *newNode = createNode(data);
  if (currentNode) 
  {
    if (before)
    {
      newNode->next = currentNode;
      newNode->prev = currentNode->prev;
      currentNode->prev->next = newNode;
      currentNode->prev = newNode;
      if (currentNode == head)
      {
        return newNode;
      }
    }
    else 
    {
      newNode->next = currentNode->next;
      newNode->prev = currentNode;
      currentNode->next->prev = newNode;
      currentNode->next = newNode;
    }
    return head;
  }

  return newNode;
}

/*****************************
 * Rejicursive helper function for inserting a node at a sorted place
 * in the list
 * @param *head a pointer to the head of the list
 * @param data the data to fill the new node with
 * @param *currentNode a pointer to the current node we are checking
 * @return The head node whether it has changed or not
 */
struct ListNode* insertSortedHelper(struct ListNode *head, int data, 
                                    struct ListNode *currentNode)
{
  /*Check if we are at head of the list */
  if (!head || head == currentNode->next)
  {
    if (currentNode && currentNode->data > data)
    {
      return insertMiddle(head, currentNode, data, 1);
    }
    return insertMiddle(head, currentNode, data, 0);
  }

  if (currentNode->data > data)
  {
    return insertMiddle(head, currentNode, data, 1);
  }

  /*Check next node recursivley*/

  return insertSortedHelper(head, data, currentNode->next); 
}

/**********************
 * Inserts a node into the list in sorted order
 * @param *head a pointer to the head of the list
 * @param data the data to be inserted into the new node
 * @return the recursive helper function
 * Calls the recursive helper function
 */
struct ListNode* insertSorted(struct ListNode* head, int data)
{
  return insertSortedHelper(head, data, head);
}

/*******************
 * Recursive helper function for remove item, keeps
 * track of head node
 * Removes the first node found with data == data
 * @param **headRef the address of where we are in the list
 * @param data the data to be removed from the list
 * @param *head the pointer to the head of the list
 * @return 0 if data is not found, otherwise 1 if it
 * is found and removed
 */
int removeItemHelper(struct ListNode **headRef, int data, 
                     struct ListNode *head)
{
  if ((*headRef)->data == data)
  {
    removeMiddle(headRef, head);
    return 1;
  }

  if ((*headRef)->next == head)
  {
    return 0;
  }

  return removeItemHelper(&(*headRef)->next, data, head);
}

/********************
 * Removes an item from the list using the 
 * recursive helper function
 * Removes the first item from the list with
 * data == data
 * @param **headRef a pointer to the address of the head node
 * @param data the data to be removed
 * @return the recursive helper function call
 * */
int removeItem(struct ListNode** headRef, int data)
{
  if (!headRef || !(*headRef))
  {
    return 0;
  }

  return removeItemHelper(headRef, data, *headRef);
}

/**************************
 * Remove a node from the middle of the list
 * @param **ref a reference to the node that is
 * going to get removed
 * @param *head a pointer to the head of the list
 * @return the data that was removed from the list
 */
int removeMiddle(struct ListNode **ref, struct ListNode *head)
{
  int retData;
  struct ListNode* tmp;
  if (*ref)
  {
    /*Set temp variable and move pointers */
    retData = (*ref)->data;
    tmp = *ref;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    if (*ref == head && (*ref)->next != head)
    {
      *ref = (*ref)->next;
    }
    /*Free node */
    free(tmp);
    return retData;
  }

  return 0;
}


/**********************
 * Pushes a node onto the stack
 * Inserts a node at the head of the linked list
 * @param *head the head of the linked list
 * @param data the data to be inserted
 * @return a pointer to the new head
 */
struct ListNode* pushStack(struct ListNode *head, int data)
{
  return insertMiddle(head, head, data, 1);
}

/**********************
 * Removes a node from the front of the stack
 * @param **headRef a pointer to the pointer of the head node
 * @return the data that was removed
 */
int popStack(struct ListNode **headRef)
{
  if (!headRef || !(*headRef))
  {
    return -1;
  }
  return removeMiddle(headRef, *headRef);
}

/**************************
 * Gets the list length recursivley, helper function for list length
 * @param *head a pointer to the head of the list
 * @param *currentNode the node we are currently on
 * @return the count of things in the list, 1 + 1 for all nodes
 */
int listLengthHelper(struct ListNode *head, struct ListNode *currentNode)
{
  if (currentNode->next == head)
  {
    return 1;
  }

  return 1 + listLengthHelper(head, currentNode->next);
}

/******************
 * Gets the list length of the list
 * @param *head the head of the list to get the list length
 * @returns the list of the length
 * Recursively counts how many nodes there are in the list
 */
int listLength(struct ListNode *head)
{
  if (!head)
  {
    return 0;
  }
  return listLengthHelper(head, head);  
}

/*****************
 * Prints out the linked list recursivley 
 * @param head a pointer to the head of the list
 * @param currentNode a pointer to the node we are currently visitng
 */
void printListHelper(struct ListNode *head, struct ListNode *currentNode)
{
  if (head == currentNode->next)
  {
    printf("%d", currentNode->data);
    return;
  }

  printf("%d, ", currentNode->data);
  printListHelper(head, currentNode->next);
}

/*****************
 * Recursively prints the list 
 * @param *head the head of the list to print out
 */
void printList(struct ListNode *head)
{
  /*Make sure we arent at end */
  if (head) 
  {
    printListHelper(head, head);
    printf("\n");
  }
  else 
  {
    printf("\n");
  }
}

/*********************
 * Frees the list recursivley gets called from free list
 * @param *head a pointer to the head of the list to keep track
 * @param currentNode a pointer to the node we are currently at
 */
void freeListHelper(struct ListNode *head, struct ListNode *currentNode)
{
  if (head == currentNode->next)
  {
    free(currentNode);
  }
  else
  {
    freeListHelper(head, currentNode->next);
    free(currentNode);
  }
}

/*******************
 * Frees the list recursivley
 * @param *head the pointer to the head of the list
 */
void freeList(struct ListNode *head)
{
  if (head)
  {
    freeListHelper(head, head);
  }
}

/*********************
 * Recursive helper function for reversing the list
 * @param **headRef the reference for the head pointer
 * @return the new head node after reversing the list
 */
struct ListNode *reverseListHelper(struct ListNode** headRef, struct ListNode *last)
{
  /*Use tmp for swaping items in list */
  struct ListNode *tmp = NULL;

  /*Swap prev and next pointers of current node*/
  tmp = (*headRef)->prev;
  (*headRef)->prev = (*headRef)->next;
  (*headRef)->next = tmp;
  /*If we are at end of list return tmp->prev/ the new head of the list*/
  if ((*headRef) == last) 
  {
    return tmp->prev;
  }
  /*other wise recursivley call the function */
  return reverseListHelper(&(*headRef)->prev, last);
}

/******************
 * Reverses a list that is pointed to by *headRef
 * @param **headRef the reference to the head of the list
 */
void reverseList(struct ListNode** headRef)
{
  if (!headRef || !(*headRef))
  {
    return;
  }
  /*Set the head pointer to the result of the reverseListHelper*/
  *headRef = reverseListHelper(headRef, (*headRef)->prev);
}

