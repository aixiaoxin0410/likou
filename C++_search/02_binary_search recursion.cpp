#include <iostream>
using namespace std;

// 二分搜索递归实现
int BinarySearch(int arr[], int i, int j, int val)
{
    if(i > j )
        return -1;
    int mid = (i + j) / 2; 
    if(arr[mid] == val)
    {
        return mid;
    }    
    else if(arr[mid] > val)
    {
        return BinarySearch(arr, i ,mid-1, val);
    }
    else
    {
        return BinarySearch(arr, mid + 1 ,j, val);
    }
}

int main()
{
    int arr[] = {12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100};
    int size = sizeof(arr)/sizeof(arr[0]);
    for(int v:arr)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << BinarySearch(arr, 0, size-1, 12) << endl;
    cout << BinarySearch(arr, 0, size-1, 45) << endl;
    cout << BinarySearch(arr, 0, size-1, 100) << endl;
    cout << BinarySearch(arr, 0, size-1, 88) << endl;
    return 0;
}