/*二叉堆C实现*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct heapStruct {
    int capacity;
    int size;
    int *array;
}HeapStruct, *PriorityQueue;

PriorityQueue initialize(int capacity);
void destroyQueue(PriorityQueue q);
void makeEmpty(PriorityQueue q);
void insert(int x, PriorityQueue q);
int deleteMin(PriorityQueue q);
int findMin(PriorityQueue q);
bool isFull(PriorityQueue q);
bool isEmpty(PriorityQueue q);

int main(void)
{
    PriorityQueue p = initialize(11);
    insert(13, p);
    insert(16, p);
    insert(19, p);
    insert(14, p);
    insert(21, p);
    insert(19, p);
    insert(26, p);
    insert(68, p);
    insert(65, p);
    insert(31, p);
    insert(32, p);
    int min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    min = deleteMin(p);
    return 0;
}

PriorityQueue initialize(int capacity)
{
    PriorityQueue q;
    if (capacity < 0)
    {
        printf("Illegal initial capacity : %d\n", capacity);
        exit(-1);
    }
    q = (PriorityQueue)malloc(sizeof(HeapStruct));
    if (NULL == q)
    {
        printf("out of memory.\n");
        exit(-1);
    }
    q->array = (int *)malloc(sizeof(int) * (capacity + 1));
    if (NULL == q->array)
    {
        printf("out of memory.\n");
        exit(-1);
    }
    q->capacity = capacity;
    q->size = 0;
    return q;
}

void destroyQueue(PriorityQueue q)
{
    if (NULL == q)
        return;
    if (NULL != q->array)
        free(q->array);
    free(q);
    return;
}

void makeEmpty(PriorityQueue q)
{
    if (NULL == q)
    {
        printf("priorityQueue is null.\n");
        return;
    }
    q->size = 0;
    return;
}

void insert(int x, PriorityQueue q)
{
    if (NULL == q)
    {
        printf("priorityQueue is null.\n");
        return;
    }
    if (isFull(q))
    {
        printf("priorityQueue is full.\n");
        return;
    }
    if (isEmpty(q))
    {
        q->array[++q->size] = x;
        q->array[0] = x;
    }
    else 
    {
        int i;
        for (i = ++q->size; q->array[i/2] > x; i /= 2)
            q->array[i] = q->array[i/2];
        q->array[i] = x;
        q->array[0] = q->array[1];
    }
    return;
}

int deleteMin(PriorityQueue q)
{
    if (NULL == q)
    {
        printf("priorityQueue is null.\n");
        exit(-1);
    }
    if (isEmpty(q))
    {
        printf("priorityQueue is empty.\n");
        exit(-1);
    }
    int minVal, lastVal;
    minVal = q->array[1];
    lastVal = q->array[q->size--];
    int i, child;
    for (i = 1; i * 2 < q->size; i = child)
    {
        child = i * 2;
        if (child != q->size && q->array[child + 1] < q->array[child])
            child++;
        if (lastVal > q->array[child])
            q->array[i] = q->array[child];
        else 
            break;
    }
    q->array[i] = lastVal;
    if (!isEmpty(q)) 
        q->array[0] = q->array[1];
    return minVal;
}

int findMin(PriorityQueue q)
{
    if (NULL == q) 
    {
        printf("PriorityQueue is null.\n");
        exit(-1);
    }
    if (isEmpty(q))
    {
        printf("PriorityQueue is empty.\n");
        exit(-1);
    }
    return q->array[1];
}

bool isFull(PriorityQueue q)
{
    if (NULL == q) 
    {
        printf("PriorityQueue is null.\n");
        exit(-1);
    }
    if (q->size == q->capacity)
        return true;
    else
        return false;
}

bool isEmpty(PriorityQueue q)
{
    if (NULL == q) 
    {
        printf("PriorityQueue is null.\n");
        exit(-1);
    }
    if (q->size == 0)
        return true;
    else 
        return false;
}