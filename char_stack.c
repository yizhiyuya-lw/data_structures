#include "char_stack_h.h"

bool isEmpty(PSTACK pStack)
{
    return pStack->top == EMPTY_INDEX;
}

bool isFull(PSTACK pStack)
{
    return pStack->top == pStack->capacity - 1;
}
PSTACK createStack(int size)
{
    PSTACK pStack;
    pStack = (PSTACK)malloc(sizeof(STACK));
    if (NULL == pStack)
    {
        exit(-1);
    }
    pStack->array = malloc(sizeof(char) * size);
    if (NULL == pStack->array)
    {
        exit(-1);
    }
    pStack->capacity = size;
    makeEmpty(pStack);
    return pStack;
}

void disposeStack(PSTACK pStack)
{
    if (NULL != pStack)
    {
        free(pStack->array);
        free(pStack);
    }
    return;
}

void makeEmpty(PSTACK pStack)
{
    pStack->top = EMPTY_INDEX;
    return;
}

void push(PSTACK pStack, char val)
{
    if (!isFull(pStack))
        pStack->array[++pStack->top] = val;

    return;
}

void pop(PSTACK pStack)
{
    if (!isEmpty(pStack))
        pStack->top--;
    return;
}

char top(PSTACK pStack)
{
    if (!isEmpty(pStack))
        return pStack->array[pStack->top];
    return '\0';
}

char topAndPop(PSTACK pStack)
{
    if (!isEmpty(pStack))
        return pStack->array[pStack->top--];
    
    return '\0';
}

