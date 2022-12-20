#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct
{
  char username[30];
  char password[30];
  int status;
} account;

typedef struct Node
{
  account acc;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct
{
  Node *root;
  Node *tail;
} linkedList;

int getLength(linkedList *list);
void printSingleList(linkedList *list);
void *createSingleList(linkedList *list);
Node *makeNewNode(account e);
Node *getNodeAt(linkedList *list, int index);
Node *insertEnd(linkedList *list, account e);
Node *insertBegin(linkedList *list, account e);
Node *insertAt(linkedList *list, account e, int pos);
Node *deleteBegin(linkedList *list);
Node *deleteEnd(linkedList *list);
Node *deleteAt(linkedList *list, int pos);
#endif
