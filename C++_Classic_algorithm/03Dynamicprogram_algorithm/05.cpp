#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cnt = 0;// 用于代码测试
string str1 = "helloworld";
string str2 = "hlweord";
int ** dp = nullptr;
int **path = nullptr; //记录最长子序列

int LCS01(string X,int n,string Y,int m)
{
    if(n < 0 || m < 0)
    {
        return 0;
    }
    if(dp[n][m] >= 0) // 查表，查子问题的解是否被求过
    {
        return dp[n][m];
    }

    cnt++; // 分治算法：628次 动态规划：40次
    
    if(X[n] == Y[m])
    {
        dp[n][m] = LCS01(X,n-1,Y,m-1) + 1;
        path[n][m] = 1; // n,m => n-1,m-1 对角线
        return dp[n][m];
    }
    else
    {
        int len1 = LCS01(X,n,Y,m-1);
        int len2 = LCS01(X,n-1,Y,m);
        if(len1 >= len2)
        {
            dp[n][m] = len1;
            path[n][m] = 2; // n,m => n,m-1 左边
        }
        else
        {
            dp[n][m] = len2;
            path[n][m] = 3; // n,m => n-1,m 上方
        }
        // return std::max(len1,len2);
        return dp[n][m];
    }
}

void BackStrace(string str1,int n,int m)
{
    if(n<0 || m<0)
    {
        return;
    }
    if(path[n][m] == 1)
    {
        BackStrace(str1,n-1,m-1); // 向对角线递归
        cout << str1[n] << " ";
    }
    else if(path[n][m] == 2)
    {
        BackStrace(str1,n,m-1); // 向左递归
    }
    else // path[n][m] = 3
    {
        BackStrace(str1,n-1,m); // 向上递归
    }
}

int main()
{
    // dp是一个n行m列
    int n = str1.size();
    int m = str2.size();
    dp = new int* [n]; // n行
    for(int i = 0; i < n; i++)
    {
        dp[i] = new int[m];
        for(int j =0 ; j<m;j++)
        {
            dp[i][j] = -1;
        }
    }

    path = new int* [n]; 
    for(int i = 0; i < n; i++)
    {
        path[i] = new int[m]();
    }

    int size = LCS01(str1,n-1,str2,m-1);
    cout << "LCS length: " << size << endl;
    cout << "cnt: " << cnt << endl;

    for(int i = 0; i < n; i++)
    {
        for(int j =0 ; j<m;j++)
        {
            if(dp[i][j] == -1)
            {
                cout << "*" << " ";
            }
            else
            {
                cout << dp[i][j] << " ";
            }

        }
        cout << endl;
    }
    cout << endl;
    
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j =0 ; j<m;j++)
    //     {
    //         cout << path[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    BackStrace(str1,n-1,m-1);

    return 0;
}