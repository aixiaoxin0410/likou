#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
硬币选择问题：有1, 3, 5分面额的硬币，给定一个面值11，问组成给定面值所需要的最少的硬币数量是多少？？？
*/

// 子问题的状态（最优解）：（9）组成价值9需要的硬币的最少数量


// 参数n表示面值，返回值表示组成面值n所需要的最少的硬币数量
int func(int n)
{
    if(n == 1 || n ==3 || n==5)
    {
        return 1;
    }
    else if(n == 2 || n ==4)
    {
        return 2;
    }
    else
    {
        int n1 = func(n-1) + 1; // 选择了一分硬币
        int n2 = func(n-3) + 1; // 选择了三分硬币
        int n3 = func(n-5) + 1; // 选择了五分硬币
        return std::min({n1,n2,n3});
    }
}

int main()
{
    int n = 11;
    int num = func(n);
    cout << "num:" << num << endl;
    return 0;
}
