#include <iostream>
using namespace std;
#include"time.h"

// 希尔排序 时间复杂度：最坏 O(n^2)，平均 O(n^1.3)，最好 O(n)，空间复杂度：O(1)，稳定性：不稳定
void ShellSort(int arr[], int size)
{
    for(int gap = size/2; gap >0; gap/=2) 
    {
        for(int i =gap;i<size;i++)  // O(n)
        {
            int val = arr[i];
            int j = i-gap;
            for(;j>=0;j-=gap) // O(n)
            {
                if(arr[j]<=val)
                {
                    break;
                }
                arr[j+gap] = arr[j];
            }
            arr[j+gap] = val;
        }        
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

    ShellSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
