#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#if 0
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

# endif

/* 
整数选择问题：给定一组整数，从里面挑选出一组整数，让选择的整数的和，和剩下的整数的和的差最小
*/

int arr[] = {12, 6, 7, 11, 16, 3, 9};
const int length = sizeof(arr)/sizeof(arr[0]);
// int x[length] = { 0 }; // 子集树辅助数组， 记录节点走向左孩子还是右孩子，代表i节点被选择&未被选择
// int bestx[length] = {0}; // 记录最优解
vector<int>x;
vector<int>bestx;

unsigned int min_diff = 0xFFFFFFFF; // 记录最小的差值
int sum = 0; // 记录所选子集数字的总和
int r = 0; // 记录未选择数字的和

// // 生成子集树
// void func(int i)
// {
//     if(i == length) // 访问到了子集树的一个叶子节点
//     {
//         // sum
//         int result = abs(sum-r);
//         if(result < min_diff)
//         {
//             min_diff = result;
//             // 需要记录一下差值的子集
//             for(int j = 0; j < length; ++j)
//             {
//                 bestx[j] = x[j];
//             }
//         }
//     }
//     else
//     {
//         r -= arr[i];
//         sum += arr[i];
//         x[i] = 1;
//         func(i+1); // 选择i节点
//         sum -= arr[i];
//         r += arr[i];

//         x[i] = 0;
//         func(i+1); // 不选择i节点
//     }
// }

// 生成子集树
void func(int i)
{
    if(i == length) // 访问到了子集树的一个叶子节点
    {
        // sum
        int result = abs(sum-r);
        if(result < min_diff)
        {
            min_diff = result;
            bestx = x;
        }
    }
    else
    {
        r -= arr[i];
        sum += arr[i];
        x.push_back(arr[i]);
        func(i+1); // 选择i节点
        sum -= arr[i];
        r += arr[i];

        x.pop_back();
        func(i+1); // 不选择i节点
    }
}

int main()
{
    for(int v : arr)
    {
        r += v;
    }
    func(0);
    // for(int i = 0; i < length; i++)
    // {
    //     if(bestx[i] == 1)
    //     {
    //         cout << arr[i] << " ";
    //     }
    // }
    for(int v:bestx)
    {
        cout << v << " ";
    }

    cout << endl;
    cout << "min:" << min_diff << endl;
    return 0;
}
