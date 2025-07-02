#include<iostream>
#include<ctime>
using namespace std;

struct Node
{
    Node(int data =0): data(data),next(nullptr){}
    int data;
    Node* next;
};

// 约瑟夫环问题 - 不带头节点的单项循坏链表应用
void Joseph(Node* head, int k, int m)
{
    Node *p = head;
    Node *q = head;

    for(int i =1; i < k; i++)
    {
        q = p;
        p = p->next;
    }

    while(q->next != head)
    {
        q = q->next;
    }

    for(;;)
    {
        for(int i =1; i < m; i++)
        {
            q = p;
            p = p->next;
        }

        cout << p->data << " ";

        if( p == q )
        {
            delete p;
            break;
        }

        q->next = p->next;
        delete p;
        p = q->next;
    }   

}

int main()
{
    Node* head = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);    
    Node* n6 = new Node(6);
    Node* n7 = new Node(7);
    Node* n8 = new Node(8);

    head->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;  
    n5->next = n6;   
    n6->next = n7;  
    n7->next = n8; 
    n8->next = head; 

    Joseph(head,1,3);

    return 0;
}

#if 0 
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
#endif


