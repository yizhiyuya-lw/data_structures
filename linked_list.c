/*
    模拟java LinkedList
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linked_list {
    int size;
    struct node * first;
    struct node * last;
} LINKED_LIST, * PLINKED_LIST;

typedef struct node {
    int val;
    struct node * pre;
    struct node * next;
} NODE, * PNODE;

PLINKED_LIST create_linked_list();
PNODE create_node(int val);
bool add_first(PLINKED_LIST plist, int val);
bool add_last(PLINKED_LIST plist, int val);
int get_first(PLINKED_LIST plist);
int get_last(PLINKED_LIST plist);
bool remove_first(PLINKED_LIST plist, int * remove_val);
bool remove_last(PLINKED_LIST plist, int * remove_val);
bool contains(PLINKED_LIST plist, int val);
int size(PLINKED_LIST plist);
void clear(PLINKED_LIST plist);
void show_list(PLINKED_LIST plist);

int main(void)
{
    PLINKED_LIST plist = create_linked_list();
    add_first(plist, 2);
    add_first(plist, 4);
    add_last(plist, 3);
    add_last(plist, 1);
    printf("size : %d\n", size(plist));
    show_list(plist);
    int remove_val;
    remove_first(plist, &remove_val);
    printf("remove_val: %d\n", remove_val);
    printf("size : %d\n", size(plist));
    show_list(plist);
    printf("last: %d\n", get_last(plist));

    printf("contains 3 : %d\n", contains(plist, 3));

    clear(plist);

    show_list(plist);
    return 0;
}

PLINKED_LIST create_linked_list()
{
    PLINKED_LIST plist = (PLINKED_LIST)malloc(sizeof(LINKED_LIST));
    if (plist == NULL)
    {
        printf("linked_list create failed, malloc method error!\n");
        exit(-1);
    }
    plist->size = 0;
    plist->first = NULL;
    plist->last = NULL;
    return plist;
}

PNODE create_node(int val)
{
    PNODE pnode = (PNODE)malloc(sizeof(NODE));
    if (pnode == NULL)
    {
        printf("create node failed, malloc method error");
        exit(-1);
    }
    pnode->val = val;
    pnode->pre = NULL;
    pnode->next = NULL;
    return pnode;
}

bool add_first(PLINKED_LIST plist, int val)
{
    PNODE pnode = create_node(val);
    if (plist->first == NULL)
    {
        plist->first = pnode;
        plist->last = pnode;
    } 
    else 
    {
        pnode->next = plist->first;
        plist->first = pnode;
    }
    plist->size++;
    return true;
}

bool add_last(PLINKED_LIST plist, int val)
{
    PNODE pnode = create_node(val);
    if (plist->last == NULL)
    {
        plist->last = pnode;
        plist->first = pnode;
    }
    else
    {
        pnode->pre = plist->last;
        plist->last->next = pnode;
        plist->last = pnode;
    }
    plist->size++;
    return true;
}

int get_first(PLINKED_LIST plist)
{
    if (plist->first == NULL)
    {
        printf("first is NULL!\n");
        exit(-1);
    }
    else
    {
        return plist->first->val;
    }
    
}

int get_last(PLINKED_LIST plist)
{
    if (plist->last == NULL)
    {
        printf("last is NULL!\n");
        exit(-1);
    }
    else
    {
        return plist->last->val;
    }
    
}

bool remove_first(PLINKED_LIST plist, int * remove_val)
{
    if (plist->first == NULL)
    {
        printf("first is NULL!\n");
        exit(-1);
    }
    else
    {
        PNODE first = plist->first;
        *remove_val = first->val;
        plist->first = first->next;
        if (plist->first == NULL) //说明只有一个元素，尾节点也要置为NULL
        {
            plist->last = NULL;
        }
        
        plist->size--;
        free(first); //释放内存
        return true;
    }
    
}
bool remove_last(PLINKED_LIST plist, int * remove_val)
{
    if (plist->last == NULL)
    {
        printf("last is NULL!\n");
        exit(-1);
    }
    else
    {
        PNODE last = plist->last;
        *remove_val = last->val;
        plist->last = last->pre;
        if (plist->last == NULL)
        {
            plist->first = NULL;
        }
        
        plist->size--;
        free(last); //释放内存
        return true;
    }
}

bool contains(PLINKED_LIST plist, int val)
{
    PNODE pnode = plist->first;
    while (pnode != NULL)
    {
        if (pnode->val == val)
        {
            return true;
        }
        else
        {
            pnode = pnode->next;
        }
    }
    return false;
}

int size(PLINKED_LIST plist)
{
    return plist->size;
}

void clear(PLINKED_LIST plist)
{
    while (plist->first != NULL)
    {
        PNODE pnode = plist->first;
        plist->first = pnode->next;
        free(pnode);
    }
    free(plist);
}

void show_list(PLINKED_LIST plist)
{
    PNODE pnode = plist->first;
    printf("[ ");
    while (pnode != NULL)
    {
        printf("%d ", pnode->val);
        pnode = pnode->next;
    }
    printf("]\n");
}