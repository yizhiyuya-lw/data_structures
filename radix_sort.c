/*
    基数排序实例
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 10 //数组长度
#define COUNT 3 //排序次数

typedef struct node {
    int val;
    struct node * next;
}NODE,* PNODE;

void initPnodeArray(PNODE * pArr, const int * iArr);
void radixSort(PNODE * pArr);
void insertLast(PNODE targetRoot, PNODE pNode);
int size(PNODE root);
void show(const PNODE * pArr);

int main(void)
{
    int arr[] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125};
    PNODE pArr[LENGTH];
    initPnodeArray(pArr, arr);
    radixSort(pArr);
    show(pArr);
    return 0;
}

void initPnodeArray(PNODE * pArr, const int * iArr)
{
    for (size_t i = 0; i < LENGTH; i++)
    {
        PNODE root = (PNODE)malloc(sizeof(NODE));
        PNODE pNode = (PNODE)malloc(sizeof(NODE));
        if (NULL == root || NULL == pNode)
        {
            exit(-1);
        }
        pNode->val = iArr[i];
        pNode->next = NULL;
        root->next = pNode;
        pArr[i] = root;
    }
    return;
}

void radixSort(PNODE * pArr)
{
    for (size_t i = 0; i < COUNT; i++)
    {
        for (size_t j = 0; j < LENGTH; j++)
        {
            PNODE root = pArr[j];
            int length = size(root);
            while (length-- > 0)
            {
                PNODE pNode = root->next;
                root->next = pNode->next;
                pNode->next = NULL;
                int val = pNode->val;
                int num = val/(int)pow(10, i) % 10;
                PNODE targetRoot = pArr[num];
                insertLast(targetRoot, pNode);
            }
        }
    }
    return;
}

void insertLast(PNODE targetRoot, PNODE pNode)
{
    PNODE aNode = targetRoot->next;
    if (NULL == aNode)
    {
        targetRoot->next = pNode;
    }
    else 
    {
        while (NULL != aNode->next)
        {
            aNode = aNode->next;
        }
        aNode->next = pNode;
    }
}

void show(const PNODE * pArr)
{
    for (size_t i = 0; i < LENGTH; i++)
    {
        PNODE root = pArr[i];
        PNODE fNode = root->next;
        while (NULL != fNode)
        {
            printf("%d  ", fNode->val);
            fNode = fNode->next;
        }
    }
    return;
}

int size(PNODE root)
{
    int length = 0;
    PNODE pNode = root->next;
    while (NULL != pNode)
    {
        length++;
        pNode = pNode->next;
    }
    return length;
}