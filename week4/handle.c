#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "file.h"
#include "handle.h"
Node *getUserAndPass(linkedList *list, char username[30],char password[30])
{
  Node *cur = list->root;
  while (cur != NULL)
  {
    if (strcmp(cur ->acc.username, username) == 0)
      {
        if (strcmp(cur ->acc.password, password) == 0)
        return cur;
      }
    cur = cur ->next;
  }
  return NULL;
}



Node *userAuth(linkedList *list, char username[1024],char password[30])
{
  int inputTime = 0;
  Node *userpas;
  userpas = getUserAndPass(list, username,password);
  if (userpas == NULL)
    return NULL;
  return userpas;
}
