#include <iostream>
using namespace std;
#include"time.h"

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

void Merge(int arr[], int l, int m, int r, int*p)
{
    int idx = 0;
    // int* p = new int[r - l + 1];
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

}

// 归并排序 O(n) * O(logn) = O(nlogn)
// 稳定
void MergeSort_old(int arr[], int begin, int end, int* p)
{
    if(begin >= end)
    {
        return;
    }
    int mid = (begin + end) / 2;
    // 先递
    MergeSort_old(arr, begin, mid, p);
    MergeSort_old(arr, mid + 1, end, p);  
    
    // 再归并 [begin, mid] [mid + 1, end] 把两个小段合并成有序的序列
    Merge(arr, begin, mid, end, p);

}

void MergeSort(int arr[], int begin, int end, int size)
{
    int *p = new int[size];
    MergeSort_old(arr, begin,end, p);
    delete[] p;
}

int partation(int arr[], int l,int r)
{
    // 记录基准数
    int val = arr[l];

    // 一次快排处理 O(n) * O(logn) = O(nlogn) log是以2为底的
    // 空间复杂度：O(logn) —— O(n) 递归的深度所占用的栈内存
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
    cout << RAND_MAX << endl;
    srand(time(0));
    const int COUNT = 100000000;
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
    heapsort(arr,COUNT);
    end = clock();
    cout << "heapsort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    QuickSort(brr,0,COUNT);
    end = clock();
    cout << "QuickSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    MergeSort(crr,0,COUNT-1,COUNT);
    end = clock();
    cout << "Merge spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    begin = clock();
    ShellSort(drr,COUNT);
    end = clock();
    cout << "ShellSort spend: " << (end-begin)*1.0/ CLOCKS_PER_SEC << "s" << endl;

    delete[] arr;
    delete[] brr;
    delete[] crr;
    delete[] drr;
}
