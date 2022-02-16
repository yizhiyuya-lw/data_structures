/*散列表-分离链接法 C实现*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int key;
    char val[32];
    struct Node * next;
}NODE, *PNODE;

typedef struct HashTab {
    int capacity;
    int size;
    PNODE * table;
}HashTable, *PHashTable;

PHashTable initHashTable(int capacity);
void destroyHashTable(PHashTable h);
PNODE find(int key, PHashTable h);
bool insert(int key, const char* val, PHashTable h);
bool delete(int key, PHashTable h);
void makeEmpty(PHashTable h);
int size(PHashTable h);
static int hash(int key, int tableSize);

int main(void)
{
    PHashTable h = initHashTable(11);
    insert(2, "two", h);
    insert(1, "one", h);
    insert(14, "one and four", h);
    insert(28, "two and eight", h);
    insert(25, "two and eight", h);
    PNODE p = find(22, h);
    p = find(14, h);
    bool b = delete(13, h);
    b = delete(1, h);
    b = delete(14, h);
    p = find(14, h);
    p = find(25, h);
    makeEmpty(h);
    p = find(25, h);
    int i = 0;
    return 0;
}

PHashTable initHashTable(int capacity)
{
    if (capacity <= 0)
    {
        printf("Illegal initial capacity : %d \n", capacity);
        exit(-1);
    }
    PHashTable h;
    h = (PHashTable)malloc(sizeof(HashTable));
    if (NULL == h) 
    {
        printf("null, malloc method error.\n");
        exit(-1);
    }
    h->capacity = capacity;
    h->size = 0;
    h->table = (PNODE*)malloc(sizeof(PNODE) * capacity);
    if (NULL == h->table)
    {
        printf("null, malloc method error.\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < h->capacity; i++)
    {
        h->table[i] = (PNODE)malloc(sizeof(NODE));
        if (NULL == h->table[i])
        {
            printf("null, malloc method error.\n");
            exit(-1);
        } 
        else 
        {
            h->table[i]->next = NULL;
        }  
    }
    return h; 
}

void destroyHashTable(PHashTable h)
{
    if (NULL == h)
        return;
    PNODE * list = h->table;
    int i;
    for (i = 0; i < h->capacity; i++)
    {
        PNODE p = list[i];
        PNODE tmp;
        while (NULL != p) 
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(h);
    return;
}

PNODE find(int key, PHashTable h)
{
    if (NULL == h || NULL == h->table) 
        return NULL;
    int index = hash(key, h->capacity);
    PNODE first = h->table[index]->next;
    while (NULL != first && first->key != key)
        first = first->next;
    return first;
}

bool insert(int key, const char* val, PHashTable h)
{
    if (NULL == h || NULL == h->table) 
    {
        printf("hashtable is null, please init.\n");
        return false;
    }
    PNODE p = find(key, h);
    if (NULL == p)
    {
        p = (PNODE)malloc(sizeof(NODE));
        if (NULL == p)
            exit(-1);
        p->key = key;
        strcpy(p->val, val);
        p->next = h->table[hash(key, h->capacity)]->next;
        h->table[hash(key, h->capacity)]->next = p;
        h->size++;
    }
    else
    {
        strcpy(p->val, val);
    }
    return true;
}

bool delete(int key, PHashTable h)
{
    if (NULL == h || NULL == h->table)
    {
        printf("hashTable is null, please init.\n");
        return false;
    }
    PNODE first = h->table[hash(key, h->capacity)];
    PNODE p = first->next;
    while (p != NULL && key != p->key)
    {
        first = first->next;
        p = p->next;
    }
    if (NULL != p)
    {
        first->next = p->next;
        free(p);
        h->size--;
    }
    return true;
}

void makeEmpty(PHashTable h)
{
    if (NULL == h || NULL == h->table)
    {
        printf("hashTable is null, please init.\n");
        return;
    }
    int i;
    PNODE* array = h->table;
    PNODE p;
    PNODE tmp;
    for (i = 0; i < h->capacity; i++)
    {
        p = array[i]->next;
        while (NULL != p)
        {
            tmp = p;
            p = p->next;
            free(tmp);
        }
        array[i]->next = NULL;
    }
    h->size = 0;
    return;
}

int size(PHashTable h)
{
    if (NULL == h)
    {
        printf("hashTable is null, please init.\n");
        return -1;
    }
    return h->size;
}

static int hash(int key, int tableSize)
{
    return key % tableSize;
}