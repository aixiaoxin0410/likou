#include<iostream>
using namespace std;
#include<ctime>

// 定义双向链表的节点类型
struct Node
{
    Node(int data =0)
        : data(data)
        , next(nullptr)
        , pre(nullptr)
    {}
    int data;
    Node* next;
    Node* pre;
};

class DoubleLink
{
public:
    DoubleLink()
    {
        head = new Node();
    }
    ~DoubleLink()
    {
        Node* p = head;
        while(p != nullptr)
        {
            head = head->next;
            delete p;
            p = head;
        }
    }

    // 头插法
    void InsertHead(int val)
    {
        Node* node = new Node(val);
        node->next = head->next;
        node->pre = head;
        if(head->next !=nullptr)
        {
            head->next->pre = node;
        }
        head->next = node; 
    }

    // 尾插法
    void InsertTail(int val)
    {
        Node* p = head;
        while(p->next != nullptr)
        {
            p = p->next;
        }

        Node* node = new Node(val);
        node->pre = p;
        p->next = node;

    }

    // 节点删除
    void Remove(int val)
    {
        Node* p = head->next;
        while(p!= nullptr)
        {
            if(p->data == val)
            {
                p->pre->next = p->next;
                if(p->next!= nullptr)
                {
                    p->next->pre = p->pre;
                }
                // 注释是删除多个节点的
                // Node* next = p->next;
                delete p;
                // p = next;
                return;
            }
            else
            {
                p = p->next;
            }
        }
    }

    // 查询
    bool Find(int val)
    {
        Node* p = head->next;
        while(p!=nullptr)
        {
            if(p->data == val)
            {
                return true;
            }
            else
            {
                p = p->next;
            }
        }
        return false;
    }

    // 展示
    void Show()
    {
        Node* p = head->next;
        while(p!=nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    
private:
    Node* head;
};

int main()
{
    srand(time(0));
    DoubleLink dlink;
    for(int i =0 ;i<10;i++)
    {
        dlink.InsertHead(rand()%100);
    }

    dlink.InsertHead(1111);
    dlink.InsertHead(1111);
    dlink.InsertHead(2222);

    dlink.Show();

    dlink.InsertTail(888);
    dlink.InsertTail(4444);
    dlink.InsertTail(888);
    dlink.Show();
    
    dlink.Remove(888);
    dlink.Show();

    if(dlink.Find(2))
    {
        cout << "找到了" << endl;
    }
    else
    {
        cout << "没有找到" << endl;
    }
    return 0;
}