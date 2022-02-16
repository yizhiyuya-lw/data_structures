/*散列表-开放定址法（平方探测法）*/
#include <stdio.h>
#include <stdlib.h>

enum KindOfEntry {
    Legitimate,
    Empty,
    Deleted
};

typedef struct hashEntry {
    int val;
    enum KindOfEntry info;
} Cell;

typedef struct hashTbl {
    int capacity;
    Cell* table;
}* HashTable;

HashTable initializeTable(int capacity);
int find(int key, HashTable h);
void insert(int key, HashTable h);
void delete(int key, HashTable h);
static int hash(int key, int size);

int main(void)
{
    return 0;
}

HashTable initializeTable(int capacity)
{
    HashTable h;
    int i;
    if (capacity < 0)
    {
        printf("Illegal initial capacity : %d \n", capacity);
        exit(-1);
    }
    h = (HashTable)malloc(sizeof(struct hashTbl));
    if (NULL == h)
    {
        printf("null, malloc method error.\n");
        exit(-1);
    }
    h->capacity = capacity;
    h->table = (Cell*)malloc(sizeof(Cell) * capacity);
    if (NULL == h->table)
    {
        printf("null, malloc method error.\n");
        exit(-1);
    }
    for (i = 0; i < capacity; i++)
        h->table[i].info = Empty;
    return h;
}

int find(int key, HashTable h)
{
    int currPos;
    int collisionNum = 0;
    currPos = hash(key, h->capacity);
    while (h->table[currPos].info != Empty && h->table[currPos].val != key)
    {
        currPos += 2 * ++collisionNum - 1;
        if (currPos >= h->capacity)
            currPos -= h->capacity;
    }
    return currPos;
}

void insert(int key, HashTable h)
{
    int pos;
    pos = find(key, h);
    if (h->table[pos].info != Legitimate)
    {
        h->table[pos].info = Legitimate;
        h->table[pos].val = key;
    }
}

void delete(int key, HashTable h)
{
    int pos;
    pos = find(key, h);
    h->table[pos].info = Empty;
}

static int hash(int key, int size)
{
    return key % size;
}