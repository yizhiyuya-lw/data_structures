/*
    模拟java ArrayList
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_CAPACITY 4 //默认数组长度
#define DAFAULT_EXPANSION_FACTOR 2 //默认扩容因子

typedef struct array_list {
    int * elementData;
    int length;
    int size;
    int expansionFactor; //扩容因子，例如为2，则将原有数组扩容为两倍
} ArrayList;

bool create_default_list(ArrayList * arrayList);
bool create_special_list(ArrayList * arrayList, int length, int expansionFactor);
bool is_empty(ArrayList * arrayList);
bool is_full(ArrayList * arrayList);
void clear(ArrayList * arrayList);
void resize(ArrayList * arrayList);
int get_size(ArrayList * arrayList);
bool contains(ArrayList * arrayList, int val);
int get(ArrayList * arrayList, int index);
bool insert(ArrayList * arrayList, int val);
bool replace(ArrayList * arrayList, int index, int val);
bool del(ArrayList * arrayList, int index, int * del_val);
void sort(ArrayList * arrayList);
void show(ArrayList * arrayList);

int main(void)
{
    int del_val;
    ArrayList arrayList;
    create_default_list(&arrayList);

    show(&arrayList);

    insert(&arrayList, 44);
    insert(&arrayList, 22);
    insert(&arrayList, 33);
    insert(&arrayList, 11);
    insert(&arrayList, 55);
    show(&arrayList);
    printf("current arrayList length: %d\n", arrayList.length);
    sort(&arrayList);
    show(&arrayList);
    replace(&arrayList, 2, 66);
    show(&arrayList);
    del(&arrayList, 3, &del_val);
    show(&arrayList);
    printf("current arrayList size: %d\n", get_size(&arrayList));
    printf("del_val : %d\n", del_val);
    clear(&arrayList);
    return 0;
}

bool create_default_list(ArrayList * arrayList)
{
    arrayList->expansionFactor = DAFAULT_EXPANSION_FACTOR;
    arrayList->length = DEFAULT_CAPACITY;
    arrayList->size = 0;
    arrayList->elementData = (int *)malloc(sizeof(int) * arrayList->length);
    return true;
}

bool create_special_list(ArrayList * arrayList, int length, int expansionFactor)
{
    arrayList->expansionFactor = expansionFactor;
    arrayList->length = length;
    arrayList->size = 0;
    arrayList->elementData = (int *)malloc(sizeof(int) * length); //懒加载
    return true;
}

bool is_empty(ArrayList * arrayList) 
{
    return arrayList->elementData == NULL || arrayList->size == 0;
}

bool is_full(ArrayList * arrayList)
{
    return arrayList->size == arrayList->length;
}

void clear(ArrayList * arrayList) //清空数据，size置为0
{
    free(arrayList->elementData);
    arrayList->size= 0 ;
}

void resize(ArrayList * arrayList)
{
    int curr_count = arrayList->length * arrayList->expansionFactor;
    arrayList->elementData = (int *)realloc(arrayList->elementData, sizeof(int) * curr_count);
    if (arrayList->elementData == NULL)
    {
        printf("resize failed\n");
        exit(-1);
    }
    arrayList->length = curr_count;
}

int get_size(ArrayList * arrayList)
{
    return arrayList->size;
}

bool contains(ArrayList * arrayList, int val)
{
    int size = get_size(arrayList);
    for (int i = 0; i < size; i++)
    {
        if (arrayList->elementData[i] == val)
        {
            return true;
        }
        
    }
    return false;
}

int get(ArrayList * arrayList, int index)
{
    if (index < 0 || index > arrayList->size)
    {
        printf("index: %d, is not validate", index);
        exit(0);
    }
    return arrayList->elementData[index];
}

bool insert(ArrayList * arrayList, int val)
{
    if (is_full(arrayList))
    {
        resize(arrayList);
    }
    arrayList->elementData[arrayList->size++] = val;
    return true;
}

bool replace(ArrayList * arrayList, int index, int val)
{
    if (index < 0 || index >= arrayList->size)
    {
        printf("index: %d is not validate", index);
        return false;
    }
    arrayList->elementData[index] = val;
    return true;
}

bool del(ArrayList * arrayList, int index, int * del_val)
{
    if (index < 0 || index > arrayList->size - 1)
    {
        printf("index: %d is not validate", index);
        return false;
    }
    //当前下标数据移除，下标后面的数往前移
    *del_val = arrayList->elementData[index];
    for (int i = index+1; i < arrayList->size; i++)
    {
        arrayList->elementData[i-1] = arrayList->elementData[i];
    }
    arrayList->size--;
    
}

void sort(ArrayList * arrayList)
{
    //冒泡排序实现
    if (is_empty(arrayList))
    {
        printf("arrayList is empty");
        return;
    }
    int i,j;
    for (i = 0; i < arrayList->size - 1; i++)
    {
        for (j = i + 1; j < arrayList->size; j++)
        {
            if (arrayList->elementData[i] > arrayList->elementData[j])
            {
                int tmp = arrayList->elementData[i];
                arrayList->elementData[i] = arrayList->elementData[j];
                arrayList->elementData[j] = tmp;
            }
        }
    }
}

void show(ArrayList * arrayList)
{
    if (is_empty(arrayList))
    {
        printf("arrayList: []\n");
        return;
    }
    printf("[ ");
    for (int i = 0; i < arrayList->size; i++)
    {
        printf("%d ", arrayList->elementData[i]);
    }
    printf("]\n");   
}