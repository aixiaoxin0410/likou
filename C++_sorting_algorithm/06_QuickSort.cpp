#include <iostream>
using namespace std;
#include"time.h"

int partation(int arr[], int l,int r)
{
    // 记录基准数
    int val = arr[l];

    // 一次快排处理 O(n) * O(logn) = O(nlogn) log是以2为底的
    // 空间复杂度：O(logn) 递归的深度所占用的栈内存
    // 最坏的时间复杂度：O(n^2) 
    while (l<r)
    {
        while(arr[r] > val && l < r)
        {
            r--;
        }
        if(l<r)
        {
            arr[l] = arr[r];
            l++;
        }
        while(arr[l] < val && l < r)
        {
            l++;
        }
        if(l<r)
        {
            arr[r] = arr[l];
            r--;
        }
    }
    
    // l == r 的位置，就是放基准数的位置
    arr[l] = val;
    return l;
}

void QuickSort(int arr[], int begin, int end)
{
    if(begin >= end) // 快速排序递归结束的条件
    {
        return;
    }

    // 在[begin,end]区间的元素进行一次快排分割处理
    int pos = partation(arr,begin,end);

    // 对基准数的左边和右边的序列，再分别进行快排
    QuickSort(arr,begin, pos-1);
    QuickSort(arr,pos+1, end);    
}

int main()
{
    srand(time(0));
    int arr[10];
    for(int i = 0 ;i < 10; i ++)
    {
        arr[i] = rand()% 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    QuickSort(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}