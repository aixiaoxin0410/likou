#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
No        1 2 3 4 5 6  7  8  9  10 11 12    c =12
1(8,6)    0 8 8 8 8 15 15 15 15 15 21 21    no
2(6,4)    0 8 8 8 8 15 15 15 15 15 21 21    no
3(4,7)    0 8 8 8 8 15 15 15 15 15 21 21    yes 8 
4(2,8)    0 8 8 8 8 8  14 14 14 14 14 14    yes 2 8 - 2 = 6
5(5,6)    0 0 0 0 6 6 6  6  6  6  6  6      yes
*/

int main()
{
    int w[] = {8,6,4,2,5};
    int v[] = {6,4,7,8,6};
    int n = sizeof(w)/sizeof(w[0]) - 1;
    int c = 12;
    // 定义dp数组记录子问题的解
    int **dp = nullptr;
    dp = new int*[n+1];
    for(int i = 0; i< n+1;i++)
    {
        dp[i] = new int[c+1](); // dp数组的元素内容全部初始化为0
    }

    // 先填写初始状态的值 填写dp二维数组的最后一行 物品n
    for(int j =1;j<=c;j++)
    {
        if(w[n] > j) // 第n个物品的状态 大于 背包剩余容量
        {
            dp[n][j] = 0; 
        }
        else
        {
            // 第n个物品的重量 小于等于 背包的剩余重量
            dp[n][j] = v[n];
        }
    }

    // 从n-1 >= 0 行开始 表示所选择的物品是i,i+1,...,n
    for(int i = n-1;i>=0;i--)
    {
        for(int j = 1; j<=c;j++)
        {
            if(w[i] > j) // 第i个物品无法装入背包
            {
                dp[i][j] = dp[i+1][j];
            }
            else
            {
                dp[i][j] = std::max(dp[i+1][j],v[i]+dp[i+1][j-w[i]]);
            }
        }
    }

    // 打印dp数组
    for(int i = 0;i<=n;i++)
    {
        for(int j =1;j<=c;j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // 释放dp数组的内存
    for(int i =0; i<n+1;i++)
    {
        delete[] dp[i];
    }
    delete[] dp;
    return 0;
}
