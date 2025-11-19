#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

/* 
挑选数字:有一组整数，请挑选出一组数字，让他们的和等于指定的值,存在解打印，不存在打印。
*/

int arr[] = {12, 6, 7, 11, 16, 3, 8, 4};
const int length = sizeof(arr)/sizeof(arr[0]);
vector<int>x; // 记录子集中选择的元素
vector<int>bestx; // 记录最优解
int sum = 0; // 记录子集中所选数字的和
int r = 0; // 记录未选择数字的和
unsigned int min_diff = 0xFFFFFFFF; // 记录最小的差值
int left_diff = length; // 记录未处理的数字的个数
int cnt = 0; // 记录遍历的子集的个数，用于测试

void func(int i)
{
    if(i == length)
    {
        cnt++;
        if(x.size() != length /2)
        {
            return;
        }
        // 得到子集树的一个解，对应一个叶子节点
        int result = abs(sum-r);
        if(result < min_diff)
        {
            min_diff = result;
            bestx = x;
        }
    }
    else
    {
        left_diff--; // 表示处理i节点，表示剩余的未处理的元素的个数
        if(x.size() < length /2) // 剪左树枝，提高算法效率。选择数字的前提：还未选择够n个整数
        {
            sum += arr[i];
            r -= arr[i];
            x.push_back(arr[i]);
            func(i+1); // 遍历i的左孩子，表示选择i号位元素
            sum -= arr[i];
            r += arr[i];
            x.pop_back();
        }

        // 这里右孩子可不可以剪枝呢？
        // 已选择的数字个数 + 未来能选择的所有数字的个数(i+1,i+2......n) >= n个元素
        if(x.size() + left_diff >= length/2)
        {
            func(i+1); // 遍历i的右孩子，表示不选择i号位元素
        }

        // 当前i节点已处理完成，回溯到其父节点了
        left_diff++;
    }
}
int main()
{
    for(int v : arr)
    {
        r += v;
    }
    func(0);
    for(int v:bestx)
    {
        cout << v << " ";
    }

    cout << endl;
    cout << "min:" << min_diff << endl;
    cout << "cnt:" << cnt << endl;
    return 0;
}