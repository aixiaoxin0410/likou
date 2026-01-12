#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int ar[] = {5,3,4,1,8,6,7,10};
    const int n = sizeof(ar) / sizeof(ar[0]);
    int dp[n] = {0};
    int maxval = 0;
    for(int i = 0;i<n;i++) // O(n^2)
    {
        dp[i] = 1;
        for(int j = 0;j<i;j++)
        {
            if(ar[j] <= ar[i] && 1+dp[j] > dp[i])
            {
                dp[i] = 1 + dp[j];
            }
        }
        if(dp[i] > maxval)
        {
            maxval = dp[i];
        }
    }
    cout << "maxval: " << maxval << endl;
    return 0;
}