#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
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
