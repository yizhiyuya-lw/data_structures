#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY_INDEX -1

typedef struct node {
    int capacity;
    int top;
    char * array;
}STACK, * PSTACK;

bool isEmpty(PSTACK pStack);
bool isFull(PSTACK pStack);
PSTACK createStack(int size);
void disposeStack(PSTACK pStack);
void makeEmpty(PSTACK pStack);
void push(PSTACK pStack, char val);
void pop(PSTACK pStack);
char top(PSTACK pStack);
char topAndPop(PSTACK pStack);