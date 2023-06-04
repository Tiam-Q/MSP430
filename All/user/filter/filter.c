#include "filter.h"


//���������ڿӷ���
void QuickSort(float* a, int begin, int end)
{
    if (begin >= end)//��ֻ��һ�����ݻ������в�����ʱ������Ҫ���в���
        return;

    int left = begin;//L
    int right = end;//R
    int key = a[left];//��������γ�һ����λ
    while (left < right)
    {
        //right������С
        while (left < right&&a[right] >= key)
        {
            right--;
        }
        //���
        a[left] = a[right];
        //left���ң��Ҵ�
        while (left < right&&a[left] <= key)
        {
            left++;
        }
        //���
        a[right] = a[left];
    }
    int meeti = left;//L��R��������
    a[meeti] = key;//��key�����λ

    QuickSort(a, begin, meeti - 1);//key�������н��д˲���
    QuickSort(a, meeti + 1, end);//key�������н��д˲���
}


/**********************************************
 * @abstract: ��ֵ�˲� ���ý�������
 * @Input:��������͸���
 * @Return:������ֵ
 *********************************************/
float Median_Filter (float a[],int n)
{
    QuickSort(a, 0, n-1);

    return a[n/2];
}





/**********************************************
 * @abstract: ��ֵ�˲� ���ø�˹����
 * @Input:��������͸���
 * @Return:�����ֵ
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




