#include <iostream>
#include <algorithm>
using namespace std;
#include <queue>

// 分支限界算法 - 01背包问题  FIFO队列  优先级队列
int w[] = {16,15,15}; // 物品的重量
int v[] = {45,25,25}; // 物品的价值
int c = 30; // 背包的容量
const int n = sizeof(w) / sizeof(w[0]); // 物品的重量

int cw = 0; // 已选择物品的重量
int cv = 0; // 已选择物品的价值
int bestv = 0; // 装入背包的物品的最优价值

struct Node
{
    Node(int w,int v, int l, Node* p ,bool left)
    {
        weight = w;
        value = v;
        level = l;
        parent = p;
        isleft = left;
    }
    int weight; // 已选择物品的总重量
    int value; // 已选择物品的总价值
    int level; // 节点所在的层数
    Node* parent; // 记录父节点
    bool isleft; // 节点是否选择

};

Node* bestnode = nullptr; // 记录最优解的叶子节点
queue<Node*> que; // 记录广度遍历队列

void AddLiveNode(int w,int v, int l, Node* parent ,bool isleft)
{
    Node* node = new Node(w,v,l,parent,isleft);
    que.push(node);

    if(l == n && v == bestv)
    {
        bestnode = node;
    }
}

int MaxBound(int i)
{
    int bound = 0;
    for(int k = i + 1;k <n ;k++)
    {
        bound += v[k];
    }
    return bound;
}

int main()
{
    int i = 0; // 起始的层数
    Node* node = nullptr; // 记录父节点
    while(i < n)
    {
        // 选择物品i
        int wt = cw + w[i];
        if(wt <= c)
        {
            if(cv + v[i] > bestv)
            {
                bestv = cv + v[i];
            }

            // 把左孩子加入活结点队列当中
            AddLiveNode(cw+w[i],cv+v[i],i+1,node,true);
        }

        // 不选择物品i
        int upbound = MaxBound(i);
        if(cv + upbound >= bestv)
        {
            AddLiveNode(cw,cv,i+1,node,false);
        }

        node = que.front();
        que.pop();
        i = node->level;
        cw = node->weight;
        cv = node->value;
    }

    cout << bestv << endl;
    int x[n] = {0};
    for(int j = n-1;j>=0;j--)
    {
        x[j] = bestnode->isleft ? 1:0;
        bestnode = bestnode->parent; 
    }

    for(int v:x)
    {
        cout << v << " ";
    }
    return 0;
}