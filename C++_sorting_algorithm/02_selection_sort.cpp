#include <iostream>
using namespace std;
#include"time.h"

void BubbleSort(int arr[], int size)
{
    for(int i = 0; i < size - 1; i++) // 趟数 O(n)
    {
        bool flag = false;
        // 一趟的处理
        for(int j = 0; j < size - 1 - i; j++)   // O(n)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = true;
            }
        }
        if(!flag)
        {
            // 如果没有做任何的数据交换，那么说明数据已经有序了
            return;
        }
    }
}

// 选择排序 // O(n) * O(n) = O(n^2)，空间复杂度：O(1)，稳定性：不稳定
void SelectionSort(int arr[], int size)
{
    for(int i=0 ;i< size-1;i++) // O(n)
    {
        int min = arr[i];
        int k = i;
        for(int j =i+1; j < size;j++) // O(n)
        {  
            if(arr[j] < min)
            {
                min = arr[j];
                k = j;
            }
        }
        if(k!=i)
        {
            int tmp = arr[i];
            arr[i] = arr[k];
            arr[k] = tmp;
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

    // BubbleSort(arr, sizeof(arr)/sizeof(arr[0]));
    SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}