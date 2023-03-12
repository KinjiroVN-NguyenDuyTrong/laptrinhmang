#ifdef __FILE_H__
#define __FILE_H__
#include "linkedlist.h"

void readFile();
void readFileToList(linkedList *list);
void writeListToFile(linkedList *list);
void appendDataToFile(FILE *file, nodeValType val);
int getUserAndPass(linkedList *list, char username[30],char password[30]);
Node *userAuth(linkedList *list, char username[30],char password[30]);

#endif