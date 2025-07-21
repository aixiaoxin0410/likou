#include <iostream>
using namespace std;
#include "time.h"
#include<functional>

// 优先级队列实现 priority_queue push pop top empty size
class priorityqueue
{
public:
    using Comp = function<bool(int,int)>;
    priorityqueue(int cap = 20, Comp comp = greater<int>())
        : size(0)
        , cap(cap)
        , comp(comp)
    {
        que = new int[cap];
    }

    ~priorityqueue()
    {
        delete[] que;
        que = nullptr;
    }

    
public:
    // 入堆操作
    void push(int val)
    {
        // 判断扩容
        if(size == cap)
        {
            int* p = new int[2*cap];
            memcpy(p, que, cap*sizeof(int));
            delete que;
            que = p;
            cap *= 2;
        }
        // 只有一个元素，不用进行堆的上浮调整
        if(size == 0 )
        {
            que[size] = val;
        }
        else
        { 
            // 堆里面有多个元素，需要进行上浮调整
            siftup(size,val);
        }
        size++;
    }

    // 出堆操作
    void pop()
    {
        if(size == 0)
            throw "container is empty!";
        size--;
        if(size>0)
        {
            siftdown(0,que[size]);  
        }
    }

    bool empty() const
    {
        return size == 0;
    }

    int top() const
    {
        if(size ==0)
            throw "container is empty";
        return que[0];
    }

    int size_q() const
    {
        return size;
    }
    
private:
    // 入堆上浮调整 O(logn)
    void siftup(int i, int val)
    {
        while(i>0) // 最多计算到根节点( 0号位 )
        {
            int father = (i - 1) / 2;
            if(comp(val,que[father]))
            {
                que[i] = que[father];
                i = father;
            }
            else
            {
                break;
            }
        }
        // 把val放到i的位置 
        que[i] = val;
    }

        // 入堆下沉调整 O(logn)
    void siftdown(int i, int val)
    {
        // i下沉不能超过最后一个有孩子的节点
        while(i < size /2 ) 
        {   
            int child = 2*i + 1; // 第i个节点的孩子
            if( child + 1 < size && comp(que[child+1], que[child]))
            {
                child = child + 1; // 如果i节点i右孩子的值大于左孩子，child记录右孩子的下标
            }

            if(comp(que[child],val))
            {
                que[i] = que[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        // 把val放到i的位置 
        que[i] = val;
    }

private:
    int size; // 数组元素个数
    int* que; // 指向动态扩容数组
    int cap; // 数组总空间大小
    Comp comp; // 比较器对象

};

int main()
{
    // priorityqueue pq; // 基于大根堆实现的优先级队列
    priorityqueue pq(10,[](int a,int b ){ return a<b;});
    srand(time(0));
    for(int i = 0; i <10; i++)
    {
        pq.push(rand()%100);
    }

    while(!pq.empty())
    {
        cout << pq.top() << endl;
        pq.pop();
    }

    cout << endl;
    return 0;
}