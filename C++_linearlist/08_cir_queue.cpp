#include<iostream>
using namespace std;

class Queue
{
public:
    Queue(int size =10) // push pop front back empty size
    :qcap(size)
    ,front(0)
    ,rear(0)
    {
        qQue = new int[qcap];
    }
    ~Queue()
    {
        delete[] qQue;
        qQue = nullptr;
    }

    // 入队 O(1)
    void push(int val)
    {
        if((rear + 1) % qcap == front)
        {
            expand(2*qcap);
        }

        qQue[rear] = val;
        rear = (rear + 1) % qcap;
    } 

    // 出队 O(1)
    void pop()
    {
        if(front == rear)
            throw "queue is empty";
        front = (front + 1) % qcap;
    }

    // 队头元素
    int first() const
    {
        if(front == rear)
            throw "queue is empty";
        return qQue[front];
    }

    // 队尾元素 
    int back() const
    {
        return qQue[( (rear - 1 + qcap ) % qcap )];
    }

    // 判断队列是否为空
    bool empty() const
    {
        return front == rear;
    }

    int size() const
    {
        // 遍历一遍统计队列元素个数 O(n)
        int size = 0;
        for(int i = front; i != rear; i = (i + 1) %  qcap)
        {
            size++;
        }
        return size;
    }

private:

    // 扩容队列
    void expand(int size)
    {
        int* p = new int[size];
        int i = 0;
        int j = front;
        for(; j!= rear; j = (j + 1) % qcap, i++)
        {
            p[i] = qQue[j];
        }
        delete qQue;
        qQue = p;
        front = 0;
        rear = i;
        qcap = size;
    }

    int* qQue;
    int front;
    int rear;
    int qcap;
};

int main()
{
    Queue que;
    int arr[] = {12,4,56,7,89,31,53,75};
    for(int v : arr)
    {
        que.push(v);
    }
    
    cout << que.first() << endl;
    cout << que.back() << endl;

    que.push(100);
    que.push(200);
    que.push(300);

    cout << que.back() << endl;

    while(!que.empty())
    {
        cout << que.first() << " "<< que.back() << endl;
        que.pop();
    }

    cout << "队列为空" << endl;
}

