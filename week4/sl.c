#include <stdio.h>
#include <stdlib.h>
#include "sl.h"

Person *makePerson(Person ps)
{
  Person *newPerson = (Person *)malloc(sizeof(Person));
  newPerson->id = ps.id;
  newPerson->name[256] = ps.name;
  newPerson->w = ps.w;
  newPerson->h = ps.h;
  newPerson->age = ps.age;
  newPerson->leftChild = NULL;
  newPerson->rightChild = NULL;
  return newPerson;
}

Person* find(Person* r, int id){
if(r == NULL) return NULL;
if(r->id == id) return r;
Person* p = find(r->leftChild,id);
if(p != NULL) return p;
return find(r->rightChild,id);
}

void addLeftChild(int id, Person left){
Person* pu = find(root,id);
if(pu == NULL){
printf("Not found %d\n",id); return;
}
if(pu->leftChild != NULL){
printf("Person %d has already leftChild\n",id); return;
}
pu->leftChild = makePerson(left);
}

void addRightChild(int id, Person right){
Person* pu = find(root,id);
if(pu == NULL){
printf("Not found %s\n",id); return;
}
if(pu->rightChild != NULL){
printf("Person %s has already rightChild\n",id); return;
}
pu->rightChild = makePerson(right);
}

Person *load(){
    Person newPerson ;
    
    root = NULL;
    int id,age;
  char name[256];
  float w,h;
  printf("Nhap id: ");
  scanf("%d",&id);
  printf("Nhap ten: ");
  scanf("%s",&name);
  printf("Nhap can nang: ");
  scanf("%f",&w);
  printf("Nhap chieu cao: ");
  scanf("%f",&h);
  printf("Nhap tuoi: ");
  scanf("%d",&age);
  newPerson.id = id;
  newPerson.name[256] = name;
  newPerson.w = w;
  newPerson.h = h;
  newPerson.age = age;
    //if(id == -2) break;// termination
    if(root == NULL) root = makePerson(newPerson);// create the root
    newPerson.leftChild = NULL;
    newPerson.rightChild = NULL;

}

void printTree(Person* r){
if(r == NULL) return;
{
    printf("id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",r->id,r->name,r->w,r->h,r->age);
}
if(r->leftChild == NULL) printf("leftChild = NULL");
else printf("id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",r->id,r->name,r->w,r->h,r->age);
if(r->rightChild == NULL) printf(", rightChild = NULL");
else printf("id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",r->id,r->name,r->w,r->h,r->age);
printf("\n");
printTree(r->leftChild);
printTree(r->rightChild);
}

void processLoad(){
load();
}

void printChildren(Person* p){
if(p->leftChild == NULL) printf(" Person %d does not has leftChild",p->id);
else printf(", LeftChild: id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",p->id,p->name,p->w,p->h,p->age);
if(p->rightChild == NULL) printf(" Person %d does not has rightChild\n",p->id);
else printf(", RightChild: id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",p->id,p->name,p->w,p->h,p->age);
}

void processFind(){
    int id;
    scanf("%d",&id);
    Person* p = find(root,id);
    if(p == NULL) printf("Not found %d\n",id);
    else {
    printf("Found node %d: ",id);
    printChildren(p);
}
}

void processPrint(){
printTree(root);
}

void processAddLeftChild(){
    Person ps;
    printf("Nhap id: ");
    scanf("%d",&ps.id);
    printf("Nhap ten: ");
    scanf("%s",&ps.name);
    printf("Nhap can nang: ");
    scanf("%f",&ps.w);
    printf("Nhap chieu cao: ");
    scanf("%f",&ps.h);
    printf("Nhap tuoi: ");
    scanf("%d",&ps.age);
    addLeftChild(ps.id,ps);
}

void processAddRightChild(){
    Person ps;
    printf("Nhap id: ");
    scanf("%d",&ps.id);
    printf("Nhap ten: ");
    scanf("%s",&ps.name);
    printf("Nhap can nang: ");
    scanf("%f",&ps.w);
    printf("Nhap chieu cao: ");
    scanf("%f",&ps.h);
    printf("Nhap tuoi: ");
    scanf("%d",&ps.age);
addRightChild(ps.id,ps);
}

int height(Person* p){
if(p == NULL) return 0;
int maxH = 0;
int hl = height(p->leftChild);
if(maxH < hl) maxH = hl;
int hr = height(p->rightChild);
if(maxH < hr) maxH = hr;
return maxH + 1;
}
void processHeight(){
int id;
scanf("%d",&id);
Person* p = find(root,id);
if(p == NULL) printf("Not found %d\n",id);
else printf("Height of %d is %d\n",id,height(p));
}

int count(Person* p){
if(p == NULL) return 0;
return 1 + count(p->leftChild) + count(p->rightChild);
}

void printLeaves(Person* p){
if(p == NULL) return;
if(p->leftChild == NULL && p->rightChild == NULL)
printf("id:%d; name:%s ; w:%f ;h:%f ;age:%d\n",p->id,p->name,p->w,p->h,p->age);
printLeaves(p->leftChild);
printLeaves(p->rightChild);
}

void processFindLeaves(){
printLeaves(root);
printf("\n");
}

void processCount(){
printf("Number of Persons = %d\n",count(root));
}


void freeTree(Person* r){
if(r == NULL) return;
freeTree(r->leftChild);
freeTree(r->rightChild);
free(r); r = NULL;
}

void main(){
while(1){
char cmd[256]; // representing the input command
printf("Enter a command: ");
scanf("%s",cmd);
if(strcmp(cmd,"Quit") == 0) break;
else if(strcmp(cmd,"Load")==0) processLoad();
else if(strcmp(cmd,"Print")==0) processPrint();
else if(strcmp(cmd,"Find")==0) processFind();
else if(strcmp(cmd,"Height")==0) processHeight();
else if(strcmp(cmd,"Count")==0) processCount();
else if(strcmp(cmd,"FindLeaves")==0) processFindLeaves();
else if(strcmp(cmd,"AddLeftChild")==0) processAddLeftChild();
else if(strcmp(cmd,"AddRightChild")==0) processAddRightChild();

}
freeTree(root);
}