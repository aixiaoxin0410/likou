#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#if 0 
/*
0-1背包问题:有一组物品，其重量分别是:w1,w2,...wn，其价值分别是v1,v2,...vn，现在有一个背包，
其容量是C，问怎么把物品装入背包，能够使背包的价值最大化？
*/

int w[] = {12,5,8,9,6}; // 物品的重量
int v[] = {9,11,4,7,8}; // 物品的价值
int c = 20; // 背包的容量
const int length = sizeof(w)/sizeof(w[0]);
vector<int>x; // 选择的物品
vector<int>bestx; // 记录最优选择的物品
int cw = 0; // 已选择物品的重量
int cv = 0; // 已选择物品的价值
int bestv = 0; // 记录装入背包的物品中的最大价值
int r = 0; // 未处理物品的总价值

void func(int i)
{
    if(i == length)
    {
        if(bestv < cv)
        {
            bestv = cv;
            bestx = x;
        }
    }
    else
    {
        r -= v[i];
        if(cw + w[i] <= c) // 已选择物品的重量 + 即将选择的第i号物品的重量
        {
            cw += w[i];
            cv += v[i];
            x.push_back(w[i]);
            func(i+1);
            cw -= w[i];
            cv -= v[i];
            x.pop_back();
        }

        // bestv cv + [i+1,i+2,...,n] 总价值 > bestv
        if(cv + r > bestv)
        {
            func(i+1);
        }

        r += v[i];
    }
}

int main()
{
    for(int val:v)
    {
        r += val;
    }
    func(0);
    for(int w:bestx)
    {
        cout << w << " ";
    }
    cout << endl;
    cout << "bestv:" << bestv << endl;
    return 0;
}



/*
解空间-排列树：
*/

void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void func(int arr[], int i, int length)
{
    if(i == length)
    {
        for(int i=0; i<length;i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else
    {
        // 生成i节点的所有孩子节点
        for(int k=i;k < length; k++)
        {
            // i k
            swap(arr,i,k);
            func(arr,i+1,length);
            swap(arr,i,k); // 一定要交换回来
        }
    }
}

int main()
{
    int arr[] = {1,2,3,4};
    int length = sizeof(arr)/sizeof(arr[0]);
    func(arr,0,length);
    return 0;
}

// 下一节课
/* ----------------------------------------*/
int cnt = 0; // 统计8皇后的排列次数

void swap(int arr[], int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

bool judge(int arr[], int i)
{
    for(int j = 0; j< i;j++) // i表示当前放置皇后棋子的位置
    {
        if(i == j || arr[i] == arr[j] || abs(i-j) == abs(arr[i] - arr[j]))
        {
            return false;
        }
    }
    return true;
}

void func(int arr[], int i, int length)
{
    if(i == length)
    {
        cnt++;
        for(int j = 0 ;j < length;j++)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
    else
    {
        for(int k = i ; k < length; k++)
        {
            swap(arr,i,k);
            if(judge(arr,i)) // 判断第i个位置的元素，是否满足8皇后的条件 0...i-1
            {
                func(arr,i+1,length); // 生成孩子节点，也就是说会生成一系列的排列方式
            } 

            swap(arr,i,k);
        }

    }

}

int main()
{
    // 把ar数组的下标当作行，下标对应的元素的值当作列
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = 8;
    func(arr,0,n);
    cout << "cnt:" << cnt << endl;
    return 0;
}

#endif

// 另一种实现全排列的代码 满足leetcode刷题测试用例
int arr[]= {1,2,3};
const int N = 3;
bool state[N]; // 记录所有元素是否被选择的状态 true : 选择了 false : 未选择
vector<int> vec;

void func(int i)
{
    if(i == N)
    {
        for(int v:vec)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        for(int k = 0; k < N; k++)
        {
            if(!state[k])
            {
                state[k] = true;
                vec.push_back(arr[k]);
                func(i+1); // k : 表示的是可选择的元素的起始下标   i : 表示层数
                vec.pop_back();
                state[k] = false;
            }

        }
    }
}

int main()
{
    func(0);
    return 0;
}