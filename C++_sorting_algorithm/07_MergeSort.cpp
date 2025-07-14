#include <iostream>
using namespace std;
#include"time.h"

void Merge(int arr[], int l, int m, int r)
{
    int idx = 0;
    int* p = new int[r - l + 1];
    int i = l;
    int j = m + 1;
    while(i <= m && j <= r)
    {
        if(arr[i] <= arr[j])
        {
            p[idx++] = arr[i++]; 
        }
        else
        {
            p[idx++] = arr[j++]; 
        }
    }

    while(i <= m)
    {
        p[idx++] = arr[i++];        
    }

    while(j <= r)
    {
        p[idx++] = arr[j++];        
    }

    // 再把合并好的大段有序的结果，拷贝到原始arr数组[l, r]区间内
    for(int i = l, j =0 ; i <= r; i++, j++ )
    {
        arr[i] = p[j];
    }

    delete[] p;
    p = nullptr;
}

// 归并排序 O(n) * O(logn) = O(nlogn)
// 稳定
void MergeSort(int arr[], int begin, int end)
{
    if(begin >= end)
    {
        return;
    }
    int mid = (begin + end) / 2;
    // 先递
    MergeSort(arr, begin, mid);
    MergeSort(arr, mid + 1, end);  
    
    // 再归并 [begin, mid] [mid + 1, end] 把两个小段合并成有序的序列
    Merge(arr, begin, mid, end);
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

    MergeSort(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}