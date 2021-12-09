/*
    栈数据结构
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int val;
    struct node * pNext;
}NODE, * PNODE;

typedef struct stack{
    int size;
    PNODE pTop;
    PNODE pBottom;
}STACK, *PSTACK;

PSTACK create_stack(void);
bool is_empty(PSTACK);
void push(PSTACK, int val);
bool pop(PSTACK, int *);
void show(PSTACK);
int get_size(PSTACK);
void clear(PSTACK);
void destroy(PSTACK);

int main(void)
{
    PSTACK pStack = create_stack();
    show(pStack);
    push(pStack, 1);
    push(pStack, 2);
    push(pStack, 3);
    push(pStack, 4);
    push(pStack, 5);
    show(pStack);
    int val;
    pop(pStack, &val);
    pop(pStack, &val);
    show(pStack);
    clear(pStack);
    show(pStack);
    push(pStack, 6);
    push(pStack, 7);
    push(pStack, 8);
    show(pStack);
    destroy(pStack);
    printf("------end-------\n");

    return 0;
}

PSTACK create_stack(void)
{
    PSTACK pStack = (PSTACK)malloc(sizeof(STACK));
    if (NULL == pStack)
    {
        printf("create stack failed, malloc method error!\n");
        exit(-1);
    }
    PNODE pBottom = (PNODE)malloc(sizeof(NODE));
    if (NULL == pBottom)
    {
        printf("create stack failed, malloc method error!\n");
        exit(-1);
    }
    pBottom->pNext = NULL;
    pStack->pTop = pBottom;
    pStack->pBottom = pBottom;
    pStack->size = 0;
    return pStack;
}

bool is_empty(PSTACK pStack)
{
    if (pStack->pTop == pStack->pBottom)
    {
        return true;
    }
    else 
    {
        return false;
    }
    
}

void push(PSTACK pStack, int val)
{
    PNODE pNode = (PNODE)malloc(sizeof(NODE));
    pNode->val = val;
    pNode->pNext = pStack->pTop;
    pStack->pTop = pNode;
    pStack->size++;
    return;
}

bool pop(PSTACK pStack, int * val)
{
    if (is_empty(pStack))
    {
        return false;
    }
    PNODE pNode = pStack->pTop;
    *val = pNode->val;
    pStack->pTop = pNode->pNext;
    pStack->size--;
    free(pNode);
    return true;
}

void show(PSTACK pStack)
{
    printf("[ ");
    if (!is_empty(pStack))
    {
        PNODE pNode = pStack->pTop;
        while(pNode != pStack->pBottom)
        {
            printf("%d ", pNode->val);
            pNode = pNode->pNext;
        }
    }
    printf("]\n");
    return;
}

int get_size(PSTACK pStack)
{
    return pStack->size;
}

void clear(PSTACK pStack)
{
    while(!is_empty(pStack))
    {
        PNODE pNode = pStack->pTop;
        pStack->pTop = pNode->pNext;
        free(pNode);
    }
    pStack->size = 0;
    return;
}

void destroy(PSTACK pStack)
{
    while(!is_empty(pStack))
    {
        PNODE pNode = pStack->pTop;
        pStack->pTop = pNode->pNext;
        free(pNode);
    }
    free(pStack->pBottom);
    free(pStack);
    pStack = NULL;
    return;
}