#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Person
{
    int id;
    char name[256];
    float w;
    float h;
    int age;
  struct Person *leftChild;
  struct Person *rightChild;
} Person;

Person * root;

Person *makePerson(Person ps);
Person* find(Person* r, int id);
void addLeftChild(int id, Person left);
void addRightChild(int id, Person right);
Person *load();
void printTree(Person* r);
void processLoad();
void processFind();
void processPrint();
void processAddLeftChild();
void processAddRightChild();
int height(Person* p);
void processHeight();
int count(Person* p);
void printLeaves(Person* p);
void processFindLeaves();
void processCount();
void freeTree(Person* r);

#endif