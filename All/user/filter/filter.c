#include "filter.h"


//快速排序（挖坑法）
void QuickSort(float* a, int begin, int end)
{
    if (begin >= end)//当只有一个数据或是序列不存在时，不需要进行操作
        return;

    int left = begin;//L
    int right = end;//R
    int key = a[left];//在最左边形成一个坑位
    while (left < right)
    {
        //right向左，找小
        while (left < right&&a[right] >= key)
        {
            right--;
        }
        //填坑
        a[left] = a[right];
        //left向右，找大
        while (left < right&&a[left] <= key)
        {
            left++;
        }
        //填坑
        a[right] = a[left];
    }
    int meeti = left;//L和R的相遇点
    a[meeti] = key;//将key抛入坑位

    QuickSort(a, begin, meeti - 1);//key的左序列进行此操作
    QuickSort(a, meeti + 1, end);//key的右序列进行此操作
}


/**********************************************
 * @abstract: 中值滤波 适用椒盐噪声
 * @Input:数据数组和个数
 * @Return:数组中值
 *********************************************/
float Median_Filter (float a[],int n)
{
    QuickSort(a, 0, n-1);

    return a[n/2];
}





/**********************************************
 * @abstract: 中值滤波 适用高斯噪声
 * @Input:数据数组和个数
 * @Return:数组均值
 *********************************************/
float Average_Filter (float a[],int n)
{
    int i = 0, sum = 0;
    for (i=0;i<=n-1;i++)
    {
        sum += a[i];
    }

    return sum/n;
}




