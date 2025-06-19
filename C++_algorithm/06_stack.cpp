#include<iostream>
using namespace std;

// 顺序栈 c++容器适配器 stack
class SeqStack
{
public:
    SeqStack(int size =10)
        :mtop(0)
        ,mcap(size)
        {
            mpStack = new int[mcap];
        }
    ~SeqStack()
    {
        delete[] mpStack;
        mpStack = nullptr;
    }

    // 入栈
    void push(int val)
    {
        if( mcap == mtop)
        {
            expand(2*mtop);
        }
        mpStack[mtop++] = val;
    }

    // 出栈
    void pop()
    {
        if(mtop == 0)
        {
            throw "stack is empty!";
        }
        mtop--;
    }

    // 获取栈顶元素
    int top() const
    {
        if(mtop==0)
        {
            throw "stack is empty!";
        }
        return mpStack[mtop-1];
    }

    // 栈空
    bool empty() const
    {
        return mtop == 0;
    }

    // 栈大小
    int size() const
    {
        return mtop;
    }

private:
    void expand(int size)
    {
        int* p = new int[size];
        memcpy(p,mpStack,sizeof(int)*mtop);
        delete[] mpStack;
        mpStack = p;
        mcap = size;
    }

private:
    int* mpStack;
    int mtop;   // 栈顶位置
    int mcap;   // 栈容量
};

int main()
{
    int arr[] = {12,4,56,7,89,31,53,75};
    SeqStack s;
    for(int v:arr)
    {
        s.push(v);
    }

    while(!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    cout << endl;
    return 0;
}