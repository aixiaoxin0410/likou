#include<iostream>
using namespace std;

void func(int arr[], int i, int length)
{
    if(i == length) // 递归结束条件
    {
        for(int j = 0 ; j<length; j++)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
    else
    {
        func(arr,i+1,length);
        func(arr,i+1,length);
    }
}

int main()
{
    int arr[] = {1,2,3};
    int length = sizeof(arr)/sizeof(arr[0]);
    func(arr,0,length);
    return 0;
}