#include<iostream>
using namespace std;

class LinkQueue
{
public:
    LinkQueue()
    {
        head = new Node();
        head->next = head;
        head->pre = head;
    }

    ~LinkQueue()
    {
        Node* p = head->next;
        while(p!= head)
        {
            head->next = p ->next;
            p->next->pre = head;
            delete p;
            p = head->next;
        }
        delete head;
        head = nullptr;
    }

    // 入队
    void push(int val)
    {
        Node* node = new Node(val);
        node->pre  = head->pre;
        node->next = head;
        head->pre->next = node;
        head->pre = node;
    }

    // 出队
    void pop()
    {
        Node* p = head->next;
        head->next = p ->next;
        p->next->pre = head;
        delete p;
    }

    // 队头元素
    int front() const
    {
        if(head->next == head)
            throw "queue is empty!";
        return head->next->data;
    }

    // 队尾元素
    int back() const
    {
        if(head->next == head)
            throw "queue is empty!";
        return head->pre->data;
    }

    // 判断队列是否为空
    bool empty() const
    {
        return head->next == head;
    }

private:
    struct Node
    {
        Node(int data =0 )
            : data(data)
            , next(nullptr)
            , pre(nullptr)
            {}
        int data;
        Node* next;
        Node* pre;      
    };

    Node* head;
};

int main()
{
    LinkQueue lq;
    int arr[] = {12,4,56,7,89,31,53,75};
    for(int v : arr)
    {
        lq.push(v);
    }
    cout << lq.front() << endl;
    cout << lq.back() << endl;

    lq.push(100);
    lq.push(200);
    lq.push(300);

    cout << lq.front() << endl;
    cout << lq.back() << endl;

    while(!lq.empty())
    {
        cout << lq.front() << " "<< lq.back() << endl;
        lq.pop();
    }
}

