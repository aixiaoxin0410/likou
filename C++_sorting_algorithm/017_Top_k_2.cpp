#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;

// 查重和top k 问题综合起来了
int main()
{
    srand(time(0));
    vector<int> vec;
    for(int i = 0; i< 1000; i++)
    {
        vec.push_back(rand()%10000);
    }

#if 0    
    // 统计重复次数最小的前3个数字
    int k = 3;
    unordered_map<int,int> map;
    for(auto key: vec)
    {
        map[key]++;
    }

    // 放入大根堆的时候，需要放key-value键值对
    using Type = pair<int,int>; // 定义类型别名，表示(数字, 出现次数)的键值对
    using Comp = function<bool(Type&,Type&)> ; // 定义比较函数类型
    priority_queue<Type, vector<Type>,Comp> maxheap
    ([](Type &a, Type &b)-> bool
    {
        return a.second < b.second;
    });

    auto it = map.begin();
    for(int i =0;i <k ;i++,++it)
    {
        maxheap.push(*it);
    }

    for(;it!= map.end();++it)
    {
        if(maxheap.top().second > it->second)
        {
            maxheap.pop();
            maxheap.push(*it);
        }
    }

    while (!maxheap.empty())
    {
        cout << "key: " << maxheap.top().first << " "
        << "cnt: " << maxheap.top().second << endl;
        maxheap.pop();
    }
    cout << endl;
#endif

    // 统计重复次数最大的前3个数字
    int k = 3;
    unordered_map<int,int> map;
    for(auto key: vec)
    {
        map[key]++;
    }

    // 放入小根堆的时候，需要放key-value键值对
    using Type = pair<int,int>; // 定义类型别名，表示(数字, 出现次数)的键值对
    using Comp = function<bool(Type&,Type&)> ; // 定义比较函数类型
    priority_queue<Type, vector<Type>,Comp> minheap
    ([](Type &a, Type &b)-> bool
    {
        return a.second > b.second;
    });

    auto it = map.begin();
    for(int i =0;i <k ;i++,++it)
    {
        minheap.push(*it);
    }

    for(;it!= map.end();++it)
    {
        if(minheap.top().second < it->second)
        {
            minheap.pop();
            minheap.push(*it);
        }
    }

    while (!minheap.empty())
    {
        cout << "key: " << minheap.top().first << " "
        << "cnt: " << minheap.top().second << endl;
        minheap.pop();
    }
    cout << endl;
}