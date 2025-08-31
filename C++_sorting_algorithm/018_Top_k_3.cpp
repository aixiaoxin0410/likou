#include <iostream>
using namespace std;

int Partation(int arr[], int begin, int end)
{
    int val = arr[begin];
    int i = begin;
    int j = end;

    while(i<j)
    {
        // 从右往左开始找，找到小于基准数的数字
        while(i < j && arr[j] > val)
        {
            j--;
        }
        if(i < j)
        {
            arr[i] = arr[j];
            i++;
        }
        // 从左往右找，找到大于基准数的数字        
        while(i < j && arr[i] < val)
        {
            i++;
        }

        if(i < j)
        {
            arr[j] = arr[i];
            j--;
        }
    }

    arr[i] = val;
    return i;
}

void SelectTopK(int arr[], int begin, int end, int k )
{
    int pos = Partation(arr,begin,end);
    if(pos == k -1 )
    {
        return;
    }
    else if(pos > k - 1)
    {
        SelectTopK(arr, begin, pos -1,k);
    }
    else
    {
        SelectTopK(arr, pos+1, end,k);
    }
}

// 快排分割求top k 问题
int main()
{
    int arr[] = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    int size = sizeof(arr) / sizeof(arr[0]);

    int k = 3;
    SelectTopK(arr,0,size-1,k);

    for(int i = 0; i < k;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

}