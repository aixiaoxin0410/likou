#include <iostream>
using namespace std;
#include "time.h"
#include<functional>

// 入堆下沉调整
void siftdown(int arr[], int i, int size)
{
    // i下沉不能超过最后一个有孩子的节点
    int val = arr[i];
    while(i < size /2 ) 
    {       
        int child = 2*i + 1; // 第i个节点的孩子
        if( child + 1 < size && (arr[child+1] > arr[child]))
        {
            child = child + 1; // 如果i节点i右孩子的值大于左孩子，child记录右孩子的下标
        }

        if(arr[child] > val )
        {
            arr[i] = arr[child];
            i = child; // i 继续指向它的孩子，一直调整到最后一个有孩子的节点处
        }
        else
        {
            break;
        }
    }
    // 把val放到i的位置 
    arr[i] = val;
}

void heapsort(int arr[],int size) // O(logn) * O(n) = O(nlogn) 不稳定
{
    int n = size - 1;
    // 从第一个非叶子节点
    for(int i = (n -1) /2;i>=0;i--)
    {
        siftdown(arr, i, size);
    }

    // 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
    for(int i = n;i>0;i--)
    {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;

        siftdown(arr,0,i);     
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

    heapsort(arr, sizeof(arr)/sizeof(arr[0]) - 1);

    for(int v : arr)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}