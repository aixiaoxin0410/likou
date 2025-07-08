#include <iostream>
using namespace std;
#include"time.h"

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

    SelectionSort(arr, sizeof(arr)/sizeof(arr[0]));

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}