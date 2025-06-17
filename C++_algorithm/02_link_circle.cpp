#include<iostream>
#include<ctime>
using namespace std;

class CircleLink
{
public:
    CircleLink()
    {
        head = new Node();
        tail = head;
        head->next = head;
    }
    ~CircleLink()
    {
        Node* p = head->next;
        while(p!=head)
        {
            head->next = p->next;
            delete p ;
            p = head->next;
        }
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    // 尾插法 O(1)
    void InsertTail(int val)
    {
        Node* node = new Node(val);
        node->next = tail->next;
        tail->next = node;
        tail = node; // 更新指针tail指向新的尾节点
    }

    // 头插法
    void InsertHead(int val)
    {
        Node* node = new Node(val);
        node->next = head->next;
        head->next = node;
        if(node->next == head)
        {
            tail = node;
        }
    }

    // 删除节点
    void Remove(int val)
    {
        Node* q = head;
        Node* p = head->next;
        while(p != head)
        {
            if(p->data == val)
            {
                q->next = p->next;
                delete p;
                if(q->next == head)
                {
                    tail = q;
                }
                return;
            }
            else
            {
                p = p->next;
                q = q->next;
            }
        }
    }

    //查询
    bool Find(int val) const
    {
        Node* p = head->next;
        while(p!= head)
        {
            if(p->data == val)
            {
                return true;
            }
            p = p->next;
        }
        return false;     
    }

    //打印
    void Show() const
    {
        Node* p = head->next;
        while(p!= head)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

private:
    struct Node
    {
        Node(int data =0): data(data),next(nullptr){}
        int data;
        Node* next;
    };
    
    Node* head;
    Node* tail;
};

int main()
{
    srand(time(0));
    CircleLink clink;

    clink.InsertHead(1000);
    clink.Show();

    for(int i =0; i<10;i++)
    {
        clink.InsertTail(rand()%100);
    }
    clink.Show();

    clink.InsertTail(24);
    clink.Show();

    clink.InsertHead(888);
    clink.Show();

    clink.Remove(1000);
    clink.Show();

    if(clink.Find(81))
    {
        cout << "找到了。" << endl;
    }
    else
    {
        cout << "没有找到。" << endl;
    }

    return 0;
}



