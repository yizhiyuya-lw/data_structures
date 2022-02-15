/*AVL树的实现*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct AvlNode {
    int val;
    int height;
    struct AvlNode* left;
    struct AvlNode* right;
}AVL_NODE, * AVL_TREE, *Position;

/*函数原型*/
void makeEmpty(AVL_TREE t);
Position find(int val, AVL_TREE t);
Position findMin(AVL_TREE t);
Position findMax(AVL_TREE t);
AVL_TREE insert(int val, AVL_TREE t);
AVL_TREE delete(int val, AVL_TREE t);
int retrieve(Position p);
void printTreeFirst(AVL_TREE t);
void printTreeMid(AVL_TREE t);
static int height(Position p);
static Position singleRotateWithLeft(Position k2);
static Position singleRotateWithRight(Position k2);
static Position doubleRotateWithLeft(Position k3);
static Position doubleRotateWithRight(Position k3);
static int max(int num1, int num2);

int main(void)
{
    AVL_TREE t = NULL;
    // t = insert(3, t);
    // t = insert(2, t);
    // t = insert(1, t);
    // t = insert(4, t);
    // t = insert(5, t);
    // t = insert(6, t);
    // t = insert(7, t);
    // t = insert(16, t);
    // t = insert(15, t);
    // t = insert(14, t);
    // t = insert(13, t);
    // t = insert(12, t);
    // t = insert(11, t);
    // t = insert(10, t);
    // t = insert(8, t);
    // t = insert(9, t);
    t = insert(11, t);
    t = insert(9, t);
    t = insert(12, t);
    t = insert(7, t);
    t = insert(10, t);
    t = insert(13, t);
    t = insert(8, t);
    //printTreeFirst(t);
    t = delete(10, t);
    printTreeFirst(t);
    //t = delete(7, t);
    //printTreeFirst(t);
    //printTreeMid(t);
    return 0;
}

void makeEmpty(AVL_TREE t)
{
    if (NULL != t)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        free(t);
    }
    return;
}

Position find(int val, AVL_TREE t)
{
    if (NULL == t)
    {
        return NULL;
    }
    if (val < t->val)
        return find(val, t->left);
    else if (val > t->val)
        return find(val, t->right);
    else 
        return t;
}

Position findMin(AVL_TREE t)
{
    if (NULL == t)
    {
        return NULL;
    }
    if (t->left == NULL)
        return t;
    else 
        return findMin(t->left);
    
}

Position findMax(AVL_TREE t)
{
    if (NULL != t) 
        while (NULL != t->right)
            t = t->right;
    return t;
}

AVL_TREE insert(int val, AVL_TREE t)
{
    if (NULL == t)
    {
        t = (AVL_TREE)malloc(sizeof(struct AvlNode));
        if (NULL == t)
            exit(-1);
        else {
            t->val = val;
            t->height = 0;
            t->left = NULL;
            t->right = NULL;
        }
    }
    else if (val < t->val)
    {
        t->left = insert(val, t->left);
        if (height(t->left) - height(t->right) == 2) //左子树高度比右子树高度大2，需要旋转
        {
            if (val < t->left->val)
                t = singleRotateWithLeft(t);
            else 
                t = doubleRotateWithLeft(t);
        }
        
    }
    else if (val > t->val)
    {
        t->right = insert(val, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (val > t->right->val)
                t = singleRotateWithRight(t);
            else 
                t = doubleRotateWithRight(t);
        }
    }
    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

AVL_TREE delete(int val, AVL_TREE t)
{
    Position tmpNode;
    if (NULL == t) 
        return NULL;
    else if (val < t->val)
    {
        t->left = delete(val, t->left);
        t->height = max(height(t->left), height(t->right)) + 1;
        if (height(t->right) - height(t->left) == 2)
        {
            if (NULL != t->right->right)
                t = singleRotateWithRight(t);
            else 
                t = doubleRotateWithRight(t);
        }
    }
    else if (val > t->val)
    {
        t->right = delete(val, t->right);
        t->height = max(height(t->left), height(t->right)) + 1;
        if (height(t->left) - height(t->right) == 2) 
        {
            if (NULL != t->left->left) 
                t = singleRotateWithLeft(t);
            else 
                t = doubleRotateWithLeft(t);
        }
    }
    else if (t->left && t->right)
    {
        tmpNode = findMin(t->right);
        t->val = tmpNode->val;
        t->right = delete(tmpNode->val, t->right);
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    else 
    {
        tmpNode = t;
        if (NULL == t->left)
            t = t->right;
        else if (NULL == t->right)
            t = t->left;
        free(tmpNode);
    }
    //删除完元素更新高度
    if(NULL != t)
    {
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    return t;
}

int retrieve(Position p)
{
    return 0;
}

void printTreeFirst(AVL_TREE t)
{
    if (NULL != t)
    {
        printTreeFirst(t->left);
        printf("%d ", t->val);
        printTreeFirst(t->right);
    }
    return;
}

void printTreeMid(AVL_TREE t)
{
    if (NULL != t)
    {
        printf("%d ", t->val);
        printTreeMid(t->left);
        printTreeMid(t->right);
    }
}

static int height(Position p)
{
    if (NULL == p)
        return -1;
    else 
        return p->height;
}

static Position singleRotateWithLeft(Position k2)
{
    Position k1;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    return k1;
}

static Position singleRotateWithRight(Position k2)
{
    Position k1;
    k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    return k1;
}

static Position doubleRotateWithLeft(Position k3)
{
    k3->left = singleRotateWithRight(k3->left);
    return singleRotateWithLeft(k3);
}
static Position doubleRotateWithRight(Position k3)
{
    k3->right = singleRotateWithLeft(k3->right);
    return singleRotateWithRight(k3);
}

static int max(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}