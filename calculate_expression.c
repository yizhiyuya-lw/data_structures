/*
    运算表达式计算
        未完成，栈存储的元素得要是字符串，使用字符只能计算10以内的数值，程序仅仅简单演示利用栈将中缀表达式转成后缀表达式，并进行计算的逻辑
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "char_stack_h.h"

#define LENGTH 7
#define STACK_SIZE 10

char* toSuffix(char* expStr);
int calculateExpression(char* expStr);
int calculate(char c, int num1, int num2);
bool isSymbol(char c);
int getPoroty(char c);

char symbolArr[] = {'+', '-', '*', '/', '%', '(', ')'};

int main(void)
{
    char * expStr = "2+3*4+(5*6+7)*8";
    printf("%s \n", expStr);
    expStr = toSuffix(expStr);
    printf("%s \n", expStr);
    int result = calculateExpression(expStr);
    printf("%d ", result);
    return 0;
}

char* toSuffix(char* expStr)
{
    int strLen = strlen(expStr);
    char* suffixStr = (char*)malloc(sizeof(char)*strLen);
    char* pChar = suffixStr;
    PSTACK pStack = createStack(STACK_SIZE);
    for (size_t i = 0; i < strLen; i++)
    {
        if (!isSymbol(expStr[i]))
        {
            *pChar = expStr[i];
            pChar ++;
        }
        else if ('(' == expStr[i])
        {
            //将 ( 入栈
            push(pStack, expStr[i]);
        }
        else if (')' == expStr[i])
        {
            //出栈
            while ('(' != top(pStack))
            {
                *pChar = topAndPop(pStack);
                pChar ++;
            }
            pop(pStack);
        }
        else
        {
            //符号是否比栈顶符号优先级低
            int strPoroty = getPoroty(expStr[i]);
            int stackPoroty = getPoroty(top(pStack));
            if (strPoroty >= stackPoroty)
            {
                //符号入栈
                push(pStack, expStr[i]);
            }
            else
            {
                while (getPoroty(top(pStack)) >= strPoroty)
                {
                    *pChar = topAndPop(pStack);
                    pChar ++;
                }
                push(pStack, expStr[i]);
            }
        }
    }
    //最后将栈中的所有元素出栈
    while (!isEmpty(pStack))
    {
        *pChar = topAndPop(pStack);
        pChar ++;
    }
    
    return suffixStr;
}

int calculateExpression(char* expStr)
{
    int result = 0;
    int len = strlen(expStr);
    PSTACK pStack = createStack(STACK_SIZE);
    for (size_t i = 0; i < len; i++)
    {
        if (!isSymbol(expStr[i]))
        {
            push(pStack, expStr[i]);
        }
        else
        {
            int num2 = topAndPop(pStack) - '0';
            int num1 = topAndPop(pStack) - '0';
            int tmpResult = calculate(expStr[i], num1, num2);
            push(pStack, tmpResult);
        }
        
    }
    result = topAndPop(pStack);
    return result;
}

int calculate(char c, int num1, int num2)
{
    switch (c)
    {
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num1 - num2;
            break;
        case '*':
            return num1 * num2;
            break;
        case '/':
            return num1 / num2;
            break;
        case '%':
            return num1 % num2;
            break;
        default:
            return 0;
            break;
    }
}

bool isSymbol(char c)
{
    for (size_t i = 0; i < LENGTH; i++)
    {
        if (symbolArr[i] == c)
        {
            return true;
        }
    }
    return false;
}

int getPoroty(char c)
{
    switch (c)
    {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '%':
            return 2;
            break;
        case '\0':
            return 0;
            break;
        default:
            return -1;
            break;
    }
}