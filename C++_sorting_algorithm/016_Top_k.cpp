#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <functional>
using namespace std;


int main()
{
    srand(time(0));
    vector<int> vec;
    for(int i = 0; i< 1000; i++)
    {
        vec.push_back(rand()%10000);
    }
#if 0
    // 求vec中值最小的前五个元素
    priority_queue<int> maxheap;

    int k = 5;

    // 由前k个元素构建一个大根堆
    for(int i =0;i<k ; i++)
    {
        maxheap.push(vec[i]);
    }

    // 遍历剩余的元素直到最后
    for(int i = k; i < vec.size(); i ++)
    {
        if(maxheap.top()> vec[i])
        {
            maxheap.pop();
            maxheap.push(vec[i]);
        }
    }

    // 输出结果
    while (!maxheap.empty())
    {
        cout << maxheap.top() << " ";
        maxheap.pop();
    }
    cout << endl;
#endif
    // 求vec中值最大的前五个元素
    priority_queue<int, vector<int>, greater<int>> minheap;

    int k = 5;

    // 由前k个元素构建一个大根堆
    for(int i =0;i<k ; i++)
    {
        minheap.push(vec[i]);
    }

    // 遍历剩余的元素直到最后
    for(int i = k; i < vec.size(); i ++)
    {
        if(minheap.top() < vec[i])
        {
            minheap.pop();
            minheap.push(vec[i]);
        }
    }

    // 输出结果
    while (!minheap.empty())
    {
        cout << minheap.top() << " ";
        minheap.pop();
    }
    cout << endl;

}
