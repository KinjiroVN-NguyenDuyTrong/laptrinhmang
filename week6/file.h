#ifdef __FILE_H__
#define __FILE_H__
#include "linkedlist.h"
void readFileToList(linkedList *list);
void writeListToFile(linkedList *list);
void appendDataToFile(FILE *file, nodeValType val);
#endif