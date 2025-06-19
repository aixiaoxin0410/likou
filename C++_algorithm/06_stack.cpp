#include<iostream>
using namespace std;
#include<ctime>

// 定义双向循坏链表的节点类型
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

//双向循坏链表
class DoubleCircleLink
{
public:
    DoubleCircleLink()
    {
        head = new Node();
        head->next = head;
        head->pre = head;
    }
    ~DoubleCircleLink()
    {
        Node* p = head->next;
        while(p != head)
        {
            head->next = p->next;
            p->next->pre = head;
            delete p;
            p = head->next;
        }
        delete head;
        head = nullptr;
    }

    // 头插法 O(1)
    void InsertHead(int val)
    {
        Node* node = new Node(val);
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node; 
    }

    // 尾插法 O(1)
    void InsertTail(int val)
    {
        Node* p = head->pre;
        Node* node = new Node(val);
        node->pre = p;
        p->next = node;
        node->next = head;
        head->pre = node;
    }

    // 节点删除
    void Remove(int val)
    {
        Node* p = head->next;
        while(p!= head)
        {
            if(p->data == val)
            {
                p->pre->next = p->next;
                p->next->pre = p->pre;
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
        while(p!=head)
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
        while(p!=head)
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

    DoubleCircleLink dclink;

    dclink.InsertHead(1111);
    dclink.InsertHead(1111);
    dclink.InsertHead(2222);

    dclink.Show();

    dclink.InsertTail(888);
    dclink.InsertTail(4444);
    dclink.InsertTail(888);
    dclink.Show();
    
    dclink.Remove(888);
    dclink.Show();
    
    if(dclink.Find(888))
    {
        cout << "找到了" << endl;
    }
    else
    {
        cout << "没有找到" << endl;
    }
    return 0;
}