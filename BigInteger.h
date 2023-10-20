
#ifndef BigInteger_H
#define BigInteger_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    int data;
    struct node *next;
}node;
struct BigInteger{
    node*head;
    int length;
};
node *newnode();
void display(struct BigInteger);
struct BigInteger initialize(char *);
struct BigInteger add(struct BigInteger,struct BigInteger);
void reverse(struct BigInteger *);
int compare(struct BigInteger,struct BigInteger);
void borrow(node*);
struct BigInteger sub(struct BigInteger,struct BigInteger);
void insertAtHead(struct node**,int);
node* addMul(node*,node*,int);
void print(node*);
void reverselist(node**);
struct BigInteger mul(struct BigInteger,struct BigInteger);
node *add2(node *,node *);
node* Subtract_bigLinkedList(node *,node *);
int isSmaller(node *,node *);
struct BigInteger div1(struct BigInteger,struct BigInteger);
#endif 