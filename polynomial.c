/*
    单链表表示多项式相加与相乘
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int coefficient;
    int exponent;
    struct node * next;
}NODE,* PNODE;

PNODE createNode(int *arr1, int *arr2, int length);
PNODE add(PNODE p1, PNODE p2);
PNODE mult(PNODE p1, PNODE p2);
void insertLast(PNODE p, PNODE node);
void show(PNODE p);
void freeNode(PNODE p);

int main(void)
{
    int arr1[] = {3,2,1};
    int arr2[] = {3,2,1};
    PNODE p1 = createNode(arr1, arr2, 3);
    show(p1);
    int arr3[] = {2,3,4};
    int arr4[] = {4,2,0};
    PNODE p2 = createNode(arr3, arr4, 3);
    show(p2);

    PNODE pAdd = add(p1, p2);
    show(pAdd);

    PNODE pMult = mult(p1, p2);
    show(pMult);
    return 0;
}

PNODE createNode(int *arr1, int *arr2, int length)
{
    PNODE pNode = (PNODE)malloc(sizeof(NODE));
    pNode->next = NULL;

    PNODE tmp = pNode;

    int i;
    for (i = 0; i < length; i++)
    {
        int coefficient = arr1[i];
        int exponent = arr2[i];
        PNODE newNode = (PNODE)malloc(sizeof(NODE));
        newNode->coefficient = coefficient;
        newNode->exponent = exponent;
        newNode->next = NULL;
        tmp->next = newNode;
        tmp = newNode;
    }
    return pNode;
}

PNODE add(PNODE p1, PNODE p2)
{
    PNODE pResult = (PNODE)malloc(sizeof(NODE));
    pResult->next = NULL;

    PNODE pTmp1 = p1->next;
    PNODE pTmp2 = p2->next;

    while(!((pTmp1 == NULL) && (pTmp2 == NULL)))
    {

        if (pTmp1 == NULL || (pTmp2->exponent > pTmp1->exponent))
        {
            insertLast(pResult, pTmp2);
            pTmp2 = pTmp2->next;
        }
        else if (pTmp2 == NULL || (pTmp1->exponent > pTmp2->exponent))
        {
            insertLast(pResult, pTmp1);
            pTmp1 = pTmp1->next;
        }
        else if (pTmp1->exponent == pTmp2->exponent)
        {
            PNODE pNew = (PNODE)malloc(sizeof(NODE));
            pNew->next = NULL;
            pNew->coefficient = pTmp1->coefficient + pTmp2->coefficient;
            pNew->exponent = pTmp1->exponent;
            insertLast(pResult, pNew);
            pTmp1 = pTmp1->next;
            pTmp2 = pTmp2->next;
        }
    }
    return pResult;
}

PNODE mult(PNODE p1, PNODE p2)
{
    PNODE pResult = (PNODE)malloc(sizeof(NODE));
    pResult->next = NULL;

    PNODE pTmp1 = p1->next;
    while (NULL != pTmp1)
    {
        PNODE tmpRes = (PNODE)malloc(sizeof(NODE));
        tmpRes->next = NULL;
        PNODE pTmp2 = p2->next;
        while (NULL != pTmp2)
        {
            PNODE pNode = (PNODE)malloc(sizeof(NODE));
            pNode->coefficient = pTmp1->coefficient * pTmp2->coefficient;
            pNode->exponent = pTmp1->exponent + pTmp2->exponent;
            pNode->next = NULL;
            insertLast(tmpRes, pNode);
            free(pNode);
            pTmp2 = pTmp2->next;
        }
        pResult = add(pResult, tmpRes);
        freeNode(tmpRes);
        pTmp1 = pTmp1->next;
    }
    return pResult;
}

void insertLast(PNODE p, PNODE node)
{
    PNODE pTmp = p;
    while (NULL != pTmp->next)
    {
        pTmp = pTmp->next;
    }
    PNODE pNode = (PNODE)malloc(sizeof(NODE));
    pNode->coefficient = node->coefficient;
    pNode->exponent = node->exponent;
    pNode->next = NULL;
    pTmp->next = pNode;
    return;
}

void show(PNODE p)
{
    while (NULL != p->next)
    {
        printf("%d--%d    ", p->next->coefficient, p->next->exponent);
        p = p->next;
    }
    printf("\n");
    return;
}

void freeNode(PNODE p)
{
    PNODE pNode;
    while (NULL != p)
    {
        pNode = p->next;
        free(p);
        p = pNode;
    }
    return;
}