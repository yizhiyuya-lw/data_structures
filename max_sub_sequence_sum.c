/*
    最大子序列之和
*/
#include <stdio.h>

int max_of_three_num(int, int, int);
int max_sub_sequence_sum_func1(const int arr[], int length);
int max_sub_sequence_sum_func2(const int arr[], int left, int right);
int max_sub_sequence_sum_func3(const int arr[], int length);

int main(void)
{
    int arr[] = {4, -3, 5, -2, -1, 2, 6, -2};
    int length = sizeof(arr)/4;

    printf("func1 result: %d \n", max_sub_sequence_sum_func1(arr, length));
    printf("func2 result: %d \n", max_sub_sequence_sum_func2(arr, 0, length - 1));
    printf("func3 result: %d \n", max_sub_sequence_sum_func3(arr, length));
    return 0;
}

/*
    三个数中最大的一个
*/
int max_of_three_num(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

/*
    算法1：循环遍历
*/
int max_sub_sequence_sum_func1(const int arr[], int length)
{
    int maxSum, sumTmp, i, j;
    maxSum = 0;

    for (i = 0; i < length; i++)
    {
        sumTmp = 0;
        for (j = i; j < length; j++)
        {
            sumTmp += arr[j];
            if (sumTmp > maxSum)
            {
                maxSum = sumTmp;
            }
        }
    }
    return maxSum;
}

/*
    分治策略--使用递归
    将整个数组分成两个部分，那最大子序列和会出现在左边部分或者右边部分或者跨越数据的中部从而占据左右两半部分
    需要计算左半部分最大值，右半部分最大值，左右连接处的最大值
*/
int max_sub_sequence_sum_func2(const int arr[], int left, int right)
{
    int maxLeftSum, maxRightSum;
    int maxLeftBorderSum, maxRightBorderSum;
    int leftBorderSum, rightBorderSum;
    int center, i;

    if (left == right) //该子序列只有一个值
    {
        if (arr[left] > 0)
            return arr[left];
        else
            return 0; 
    }

    center = (left + right) / 2;
    maxLeftSum = max_sub_sequence_sum_func2(arr, left, center); //左半部分最大值
    maxRightSum = max_sub_sequence_sum_func2(arr, center+1, right); //右半部分最大值
    
    maxLeftBorderSum = maxRightBorderSum = leftBorderSum = rightBorderSum = 0;
    //连接处最大值
    for (i = center; i >= left; i--)
    {
        leftBorderSum += arr[i];
        if(leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    for (i = center+1; i <= right; i++)
    {
        rightBorderSum += arr[i];
        if(rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    return max_of_three_num(maxLeftSum, maxRightSum, (maxLeftBorderSum + maxRightBorderSum));
}

/*
    时间复杂度为O(n)的算法
*/
int max_sub_sequence_sum_func3(const int arr[], int length)
{
    int maxSum = 0;
    int sumTmp = 0;
    int i;

    for (i = 0; i < length; i++)
    {
        sumTmp += arr[i];
        if (sumTmp > maxSum)
        {
            maxSum = sumTmp;
        }
        else if (sumTmp < 0)
        {
            sumTmp = 0;
        }
    }
    return maxSum;
}