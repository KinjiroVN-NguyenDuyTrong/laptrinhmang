#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "file.h"
#include "handle.h"
int getUserAndPass(linkedList *list, char username[30],char password[30])
{
  Node *cur = list->root;
  while (cur != NULL)
  {
    if (strcmp(cur ->acc.username, username) == 0)
      {
        if (strcmp(cur ->acc.password, password) == 0)
        {
          if(cur->acc.status==1) return 1;
          else return 0;
        }
      }
    cur = cur ->next;
  }
  return 2;
}



Node *userAuth(linkedList *list, char username[1024],char password[30])
{
  int inputTime = 0;
  /*
  Node *userpas;
  userpas = getUserAndPass(list, username,password);
  if (userpas == NULL)
    return NULL;
  return userpas;*/
  int check = getUserAndPass(list,username,password);
}
