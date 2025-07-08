#include <iostream>
using namespace std;
#include"time.h"

// 插入排序 时间复杂度：最坏，平均 O(n^2)，最好 O(n)，空间复杂度：O(1)，稳定性：稳定
void InsertionSort(int arr[], int size)
{
    for(int i =1;i<size;i++)  // O(n)
    {
        int val = arr[i];
        int j = i-1;
        for(;j>=0;j--) // O(n)
        {
            if(arr[j]<val)
            {
                break;
            }
            arr[j+1] = arr[j];
        }
        arr[j+1] = val;
    }
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

    InsertionSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
