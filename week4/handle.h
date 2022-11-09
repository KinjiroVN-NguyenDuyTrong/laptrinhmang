#ifndef __HANDLE_H__
#define __HANDLE_H__
#include "linkedlist.h"
int getUserAndPass(linkedList *list, char username[30],char password[30]);

Node *userAuth(linkedList *list, char username[30],char password[30]);
#endif