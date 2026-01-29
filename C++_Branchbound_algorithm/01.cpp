#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int w[] = {12,8,15}; // 集装箱的重量
const int n = sizeof(w)/sizeof(w[0]); // 集装箱的数量
int c = 27; // 轮船的容量
int cw = 0; // 已选择物品的重量
int bestw = 0; // 记录最优的装载量

// 描述节点类型
struct Node{
    Node(int w, int l)
    {
        weight = w;
        level = l;
    }
    int weight; // 从根节点到当前节点所选物品的总重量
    int level; // 当前节点的层数
};

// 广度优先遍历子集树的FIFO队列
queue<Node> que;
int i = 0; // 表示起始的层数，从根节点开始
int main()
{
    while(i < n) // 当前节点是第i层
    {
        // 处理左孩子
        int wt = cw + w[i];
        if(wt <= c)
        {
            // 选择物品i以后，其总重量不能超过轮船的容量
            if(wt > bestw)
            {
                bestw = wt;
            }

            // 活结点孩子入队列
            que.push(Node(cw + w[i],i+1));
        }

        // 处理右孩子，表示不选择i节点
        que.push(Node(cw,i+1));

        // 处理完i节点，它成为死节点，然后出队
        Node node = que.front();
        que.pop();

        // 恢复cw和i的值，表示从i节点跳到广度遍历的下一个节点了
        cw = node.weight;
        i = node.level;
    }

    cout << "bestw: " << bestw << endl;
    return 0;
}