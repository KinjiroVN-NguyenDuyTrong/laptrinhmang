#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"

void readFile()
{
  FILE *filename;
  char chat[1024];
  if ((filename = fopen("groupchat.txt", "r+")) == NULL)
  {
    printf("Khong tim thay filename!\n");
    return;
  }
  while (fgets(chat,1024,filename))
  {
    printf("%s\n",chat);
  }
  
  fclose(filename);
  return;
}

void addChat(char* chat)
{
  FILE *filename;

  if ((filename = fopen("groupchat.txt", "a+")) == NULL)
  {
    printf("Khong tim thay filename!\n");
    return;
  }
  
  fprintf(filename,chat);
  
  fclose(filename);
  return;
}

void readFileToList(linkedList *list)
{
  account node;
  FILE *filename;
  if ((filename = fopen("account.txt", "r+")) == NULL)
  {
    printf("Khong tim thay filename!\n");
    return;
  }
  while (!feof(filename))
  {
    int scan = fscanf(filename, "%s %s %d\n", node.username, node.password, &node.status);
    insertEnd(list, node);
  }
  fclose(filename);
}

void appendDataToFile(FILE *filename, account acc)
{
  fprintf(filename, "%s %s %d\n", acc.username, acc.password, acc.status);
}

void writeListToFile(linkedList *list)
{
  FILE *filename;
  Node *huan = list->root;
  if ((filename = fopen("taikhoan.txt", "w")) == NULL)
  {
    printf("Khong tim thay filename!\n");
    return;
  }  
  while (huan != NULL)
  {
    appendDataToFile(filename, huan->acc);
    huan = huan->next;
  }
  fclose(filename);
}

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


