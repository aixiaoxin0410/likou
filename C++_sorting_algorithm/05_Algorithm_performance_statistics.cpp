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
    const int COUNT = 100000;
    int* arr = new int[COUNT];
    int* brr = new int[COUNT];
    int* crr = new int[COUNT];
    int* drr = new int[COUNT];

    for(int i = 0;i<COUNT;i++)
    {
        int val = rand()% COUNT; 
        arr[i] = val;
        brr[i] = val;   
        crr[i] = val;
        drr[i] = val;
    }

    clock_t begin,end;

    begin = clock();
    BubbleSort(arr,COUNT);
    end = clock();
    cout << "BubbleSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;
    
    begin = clock();
    SelectionSort(brr,COUNT);
    end = clock();
    cout << "SelectionSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    InsertionSort(crr,COUNT);
    end = clock();
    cout << "InsertionSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    ShellSort(drr,COUNT);
    end = clock();
    cout << "ShellSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;
}
