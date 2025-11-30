#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#if 0
/* 
挑选数字:有一组整数，请挑选出一组数字，让他们的和等于指定的值,存在解打印，不存在打印。
*/

int arr[] = {4, 8, 12, 16, 7, 9, 3, 3};
const int length = sizeof(arr)/sizeof(arr[0]);
int number = 18; 
vector<int>vec; // 存放选择的数字

void func(int i,int number)
{
    if(number == 0)
    {
        for(int v:vec)
        {
            cout << v << " ";
        }
        cout << endl;   
    }
    else
    {
        // 以当前节点开始，把剩余元素的孩子节点生成
        for(int k = i; k<length;++k)
        {
            if(number >= arr[k]) // 剩余的元素小于number（待组成的元素值）
            {
                vec.push_back(arr[k]);
                // 初始元素组有重复数字：
                // 当前层遍历到下一层的时候 arr[k] != arr[k-1]

                // 不允许重复选择元素
                func(k+1,number - arr[k]); // 遍历孩子节点，表示arr[k]的孩子节点

                // 允许重复选择元素
                // func(k,number - arr[k]); 
                vec.pop_back();
            }

        }
    }
}
int main()
{
    func(0,number);
    return 0;
}

#endif

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