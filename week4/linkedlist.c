#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
int getLength(linkedList *list)
{
  int count = 0;
  Node *cur = list->root;
  while (cur != NULL)
  {
    cur = cur->next;
    count++;
  }
  return count;
}
void printSingleList(linkedList *list)
{
  account nodeAcc;
  if (list == NULL)
    return;
  Node *cur = list->root;
  while (cur != NULL)
  {
    nodeAcc = cur->acc;
    printf("%s\t\t%s\t\t%d\n", nodeAcc.username, nodeAcc.password, nodeAcc.status);
    cur = cur->next;
  }
  printf("\n");
}
void *createSingleList(linkedList *list)
{
  list->root = NULL;
  list->tail = NULL;
}
Node *makeNewNode(account acc)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->acc = acc;
  newNode->next = NULL;
  return newNode;
}
Node *getNodeAt(linkedList *list, int pos)
{
  if (pos <= 0)
    return list->root;
  if (pos > getLength(list))
    return list->tail;
  Node *cur = list->root;
  int i = 1;
  while (i != pos)
  {
    cur = cur->next;
    i++;
  }
  return cur;
};
Node *insertBegin(linkedList *list, account acc)
{
  Node *newNode = makeNewNode(acc);
  if ((*list).root == NULL)
  {
    (*list).root = (*list).tail = newNode;
  }
  else
  {
    newNode->next = (*list).root;
    (*list).root = newNode;
  }
  return (*list).root;
}
Node *insertEnd(linkedList *list, account e)
{
  Node *newNode = makeNewNode(e);
  if (list->root == NULL)
  {
    list->root = list->tail = newNode;
  }
  else
  {
    list->tail->next = newNode;
    list->tail = newNode;
  }
  return list->root;
};
Node *insertAt(linkedList *list, account e, int pos)
{
  Node *cur = getNodeAt(list, pos - 1);
  Node *newNode = makeNewNode(e);
  newNode->next = cur->next;
  cur->next = newNode;
  return list->root;
}
Node *deleteBegin(linkedList *list)
{
  if (list->root != NULL)
  {
    Node *newNode = list->root;
    list->root = list->root->next;
    free(newNode);
  }
  return list->root;
};
Node *deleteEnd(linkedList *list)
{
  Node *beforeTail = getNodeAt(list, getLength(list) - 1);
  beforeTail->next = NULL;
  free(list->tail);
  list->tail = beforeTail;
  return list->root;
};
Node *deleteAt(linkedList *list, int pos)
{
  if (pos > getLength(list))
    return NULL;
  Node *prevNode = getNodeAt(list, pos - 1);
  Node *currNode = getNodeAt(list, pos);
  prevNode->next = currNode->next;
  free(currNode);
  return list->root;
};
