#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
                func1(5)  参数：指定个数的斐波那契数列
        func1(4)        func1(3)
func1(3) func1(2)   func1(2) func1(1)

怎么描述子问题最优解的性质 <<==>> 问题的状态
dp[i] : 斐波那契数列中第i个数字的值
*/

// // 参数n表示斐波那契数列中数字的个数，返回相应个数的斐波那契数列数字的值
// int fabnacci(int n,int dp[])
// {
//     if(dp[n] > 0) // 子问题n之前被求解过了
//     {
//         return dp[n];
//     }
//     if(n == 1 || n == 2)
//     {
//         dp[n] = 1;
//         return 1;
//     }
//     else
//     {
//         dp[n] = fabnacci(n-1,dp) + fabnacci(n-2,dp);
//         return dp[n];
//     }
// }

// int main()
// {
//     // 1 1 2 3 5 8 13 21 34 55
//     int n = 10;
//     int* dp = new int[n+1]();
//     int val = fabnacci(n,dp);
//     cout << "val: " << val << endl;
//     return 0;
// }

/*
fabnacci:
状态：dp[i] : 斐波那契数列中第i个数字的值
状态转移方程：
dp[1] = 1;
dp[2] = 1;
dp[3] = dp[3-1] + dp[3-2] = dp[2] + dp[1] = 1+2 = 3
dp[i] = dp[i-1] + dp[i-2] i>2
*/

int main()
{
    const int n = 10;
    int dp[n+1] = {0};
    dp[1] = dp[2] = 1;
    for(int i= 3; i <= n ; i++)
    {   
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout << "dp[n]: " << dp[n] << endl;
    return 0;
}