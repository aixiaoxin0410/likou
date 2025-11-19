#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

/* 
挑选数字:有一组整数，请挑选出一组数字，让他们的和等于指定的值,存在解打印，不存在打印。
*/

int arr[] = {4, 8, 12, 16, 7, 9, 3};
const int length = sizeof(arr)/sizeof(arr[0]);
vector<int>x; // 记录选择的数字
int sum = 0; // 记录所选择数字的和
int number = 18; 
unsigned int min_diff = 0xFFFFFFFF; // 记录最小的差值
int cnt = 0;
int r = 0; // 记录未处理的数字的和

void func(int i)
{
    if(i == length)
    {
        cnt++;
        if(sum != number)
        {
            return;
        }
        for(int v:x)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        r -= arr[i]; // 处理当前i节点
        if(sum + arr[i] <= number) // 剪左树枝 已选择的数字 + 即将要选择的数字
        {
            sum += arr[i];
            x.push_back(arr[i]);
            func(i+1); // 遍历i的左孩子，表示选择i号位元素
            sum -= arr[i];
            x.pop_back();
        }

        // sum + 未来能选择的元素的总和 < 18

        if(sum + r >= number) // 剪右树枝 已选择的数字的和 + 剩余的可以被选择的数字的和(i+1,i+2......n)
        {
            func(i+1); // 遍历i的右孩子，表示不选择i号位元素
        }

        r += arr[i];
    }
}
int main()
{
    for(int v:arr)
    {
        r+=v;
    }
    func(0);
    cout << "cnt:" << cnt << endl;
    return 0;
}