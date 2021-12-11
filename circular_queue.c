/*
    循环队列
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
    int arr_length; //数组长度
    int *array; //队列长度为数组-1
    int front; //队列头
    int rear; //队列尾
}QUEUE, *PQUEUE;

PQUEUE init_queue(int queue_length);
void en_queue(PQUEUE pq, int val);
bool out_queue(PQUEUE pq, int * pval);
bool is_empty(PQUEUE pq);
bool is_full(PQUEUE pq);
void show_queue(PQUEUE pq);
void destroy(PQUEUE pq);

int main(void)
{
    PQUEUE pq = init_queue(6);

    en_queue(pq, 1);
    en_queue(pq, 2);
    en_queue(pq, 3);
    en_queue(pq, 4);
    en_queue(pq, 5);
    en_queue(pq, 6);
    en_queue(pq, 7);
    show_queue(pq);
    int out_val;
    bool result;
    result = out_queue(pq, &out_val);
    if (result)
    {
        printf("out queue success, this val: %d\n", out_val);
    }
    else
    {
        printf("out queue failed\n");
    }
    result = out_queue(pq, &out_val);
    if (result)
    {
        printf("out queue success, this val: %d\n", out_val);
    }
    else
    {
        printf("out queue failed\n");
    }
    show_queue(pq);
    return 0;
}

PQUEUE init_queue(int queue_length)
{
    PQUEUE pq = (PQUEUE)malloc(sizeof(QUEUE));
    if (NULL == pq)
    {
        printf("init queue fialed, malloc error!\n");
        exit(-1);
    }
    int *array = (int *)malloc(sizeof(int) * (queue_length - 1));
    if (NULL == array)
    {
        printf("init queue fialed, malloc error!\n");
        free(pq);
        exit(-1);
    }
    pq->arr_length = queue_length;
    pq->array = array;
    pq->front = 0;
    pq->rear = 0;
    return pq;
}

void en_queue(PQUEUE pq, int val)
{
    if (is_full(pq))
    {
        printf("queue is full.\n");
        return;
    }
    pq->array[pq->rear] = val;
    pq->rear = (pq->rear + 1) % pq->arr_length;
    return;
}

bool out_queue(PQUEUE pq, int * pval)
{
    if (is_empty(pq))
    {
        return false;
    }
    *pval = pq->array[pq->front];
    pq->front = (pq->front + 1) % pq->arr_length;
    return true;
}

bool is_empty(PQUEUE pq)
{
    if (pq->front == pq->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
bool is_full(PQUEUE pq)
{
    if (((pq->rear + 1) % pq->arr_length) == pq->front)
    {
        return true;
    }
    else{
        return false;
    }
    
}

void show_queue(PQUEUE pq)
{
    int index = pq->front;
    printf("[ ");
    while (index != pq->rear)
    {
        printf("%d ", pq->array[index]);
        index = (index + 1) % pq->arr_length;
    }
    printf("]\n");
    return;
}
void destroy(PQUEUE pq)
{
    free(pq->array);
    free(pq);
    return;
}