#include <stdio.h>
#include "linkedlist.h"

int main(int argc, char *argv[])
{
  struct ListNode* head = NULL;
  int i;

  head = insertSorted(head, 1);
  head = insertSorted(head, 5);
  head = insertSorted(head, 0);
  printf("List: ");
  printList(head);
  removeItem(&head, 1);
  removeItem(&head, 0);
  printf("List after removes: ");
  printList(head);
  printf("List Length = %d\n", listLength(head));
  
  reverseList(&head);
  printf("Reversed list: ");
  printList(head);
  freeList(head);
  head = NULL;


  /*Try to remove items from NULL list */
  removeItem(&head, 0);
  reverseList(&head);
  freeList(head);

  for (i = 0; i < 256; i++)
  {
    head = pushStack(head, (i*17 + 11) % 128 + 7);
  }

  printf("Stack: ");
  printList(head);
  printf("pop: %d\n", popStack(&head));
  printf("reversed stack: ");
  reverseList(&head);
  printList(head);
  freeList(head);
  head = NULL;

  return 0;
}
