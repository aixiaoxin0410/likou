#include<iostream>
using namespace std;

void func(int arr[], int i, int length, int x[])
{
    if(i == length) // 递归结束条件 StackOverFlow
    {
        for(int j = 0 ; j<length; j++)
        {
            if(x[j] == 1)
            {
                cout << arr[j] << " ";
            }

        }
        cout << endl;
    }
    else
    {
        // x[i] = 1; // 选择i节点
        // func(arr,i+1,length,x); // 遍历i的左孩子

        // x[i] = 0; // 不选择i节点
        // func(arr,i+1,length,x); // 遍历i的右孩子

        // 其他写法
        for(int k = 1; k>=0; k--)
        {
            x[i] = k;
            func(arr,i+1,length,x);
        }
    }
}

int main()
{
    int arr[] = {1,2,3};
    int length = sizeof(arr)/sizeof(arr[0]);
    int x[3] = { 0 };
    func(arr,0,length,x);
    return 0;
}