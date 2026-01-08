#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int n = 100;
int dp[n+1] = {0}; // dp[n]：组成价值n需要的硬币最少数量
int cnt = 0; // 代码测试

int func(int n)
{
    if(dp[n] > 0) // dp[n]这个子问题已经被求解过了
    {
        cnt++;
        return dp[n];
    }
    if(n == 1 || n == 3 || n == 5)
    {
        dp[n] = 1; // 代表了一个子问题最优解的性质（状态）
        return 1;
    }
    else if(n == 2 || n == 4)
    {
        dp[n] = 2;
        return 2;
    }
    else
    {
        int n1 = func(n-1) + 1;
        int n2 = func(n-3) + 1;
        int n3 = func(n-5) + 1;
        dp[n] = std::min({n1,n2,n3});
        return dp[n];
        // return std::min({n1,n2,n3});
    }
}

/*
问题的状态：dp[i]组成面值i所需要的最少的硬币数量
状态转移方程：
dp[0] = 0
dp[1] = 1 + dp[1-1]
dp[2] = 1 + dp[2-1] = 1 + 1 = 2
dp[3]：
      = 1 + dp[3-1] = 1 + 2 = 3 选择了3个1分硬币
      = 1(3) + dp[3-3] = 1 选择了一个3分硬币
dp[4]：
      = 1 + dp[4-1] = 1 + 1 = 2
      = 1 + dp[4-3] = 1 + 1 = 2

dp[5]：
      = 1 + dp[5-1] = 1 + dp[4] = 1 + 2 = 3
      = 1 + dp[5-3] = 1 + dp[2] = 1 + 2 = 3
      = 1 + dp[5-5] = 1 最优解，1个5分硬币

从上面的理论推导，得到下面的状态转移方程：
dp[i] = min{1 + dp[i-Vj]} i表示面值，Vj表示第j个硬币的面额，条件i >= Vj
*/

int main()
{
    // int num = func(n);
    // cout << "num:" << num << endl;
    // cout << "cnt" << cnt << endl;
    // return 0;
    int v[] = {1,3,5};
    int c = 11;
    int length = sizeof(v) / sizeof(v[0]);
    int *dp = new int[c+1](); // dp[c] dp[0] = 0
    for(int i = 1; i <= c; i++)
    {
        dp[i] = i; // 表示初始全部由1分硬币组成
        for(int j = 0; j < length; j++)
        {
            if(i >= v[j] && (1 + dp[i - v[j]]) < dp[i])
            {
                dp[i] = 1 + dp[i - v[j]];
            }
        }
    }
    cout << "dp[c]: " << dp[c] << endl;
    return 0;
}