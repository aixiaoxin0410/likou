#include<iostream>
using namespace std;
#include<ctime>

// 节点类型
struct Node
{
    Node(int data =0 ): data(data),next(nullptr)
    {

    }
    int data;
    Node *next;
};


// 单链表实现(包含很多节点Node)
class Slink
{
public:
    Slink()
    {
        head = new Node; // 给head初始化指向头节点
    }
    ~Slink()
    {
        // 节点的释放
        Node* p = head;
        while(p!=nullptr)
        {
            head = head->next;
            delete[] p;
            p = head;
        }
        head = nullptr;
    }

    // 链表的尾插法 O(n)
    void InsertTail(int val)
    {
        // 先找到当前链表的末尾节点
        // 尾节点的特征：地址域为空
        Node* p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        
        // 生成新节点
        Node* node = new Node(val);

        // 把新节点挂在尾节点的后面
        p->next = node;
        
    }

    // 链表的头插法 O(1)
    void InsertHead(int val)
    {
        // 生成新节点
        Node* node = new Node(val);
        node->next = head->next;
        head->next = node;
    }

    // 链表节点的删除 O(n)
    void Remove(int val)
    {
        Node* q = head;
        Node* p = head->next;
        while(p!= nullptr)
        {
            if(p->data == val)
            {
                // 删除一个节点本身的操作   O(1)
                q->next = p->next;
                delete p;
                return;
            }
            else
            {
                q = p;
                p = p->next;
            }
        }
    }

    // 删除多个节点 
    void RemoveAll(int val)
    {
        Node* p = head;
        Node* q = head->next;
        while(p!= nullptr)
        {
            if(p->data == val)
            {
                q->next = p->next;
                delete p;
                p = q->next;
            }
            else
            {
                q = p;
                p = p->next;
            }
        }
    }
    // 搜索 O(n)
    bool Find(int val)
    {
        Node * p = head->next;
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

    // 打印链表函数
    void Show()
    {
        Node *p = head->next;
        while(p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
private:
    Node* head; // 指向链表的头节点
    friend void ReverseLink(Slink &slink);
};

// 单链表逆序
void ReverseLink(Slink &slink)
{
    Node * head = slink.head;
    Node * p = head->next;
    if(p == nullptr)
    {
        return;
    }

    head->next = nullptr;

    while(p!=nullptr)
    {
        Node* q = p->next;
        p->next = head->next;
        head->next = p;

        p = q ;
    }

    

}

int main()
{
    srand(time(0));
    Slink slink;
    for(int i =0 ;i<10;i++)
    {
        int val = rand()%100;
        slink.InsertTail(val);
    }
    slink.Show();

    ReverseLink(slink);
    slink.Show();
}



#if 0 
int main()
{
    srand(time(0));
    Slink slink;
    for(int i =0 ;i<10;i++)
    {
        int val = rand()%100;
        slink.InsertTail(val);
        cout << val << " ";
    }
    cout << endl;
    slink.Show();

    for(int i =0 ;i<10;i++)
    {
        int val = rand()%100;
        slink.InsertHead(val);
        cout << val << " ";
    }
    cout << endl;
    slink.Show();

    slink.InsertHead(12000);
    slink.InsertHead(100);
    slink.InsertTail(1555);
    slink.Show();

    slink.Remove(12000);
    slink.Show();

    slink.InsertTail(111);
    slink.InsertTail(111);
    slink.InsertTail(111);
    slink.InsertHead(111);
    slink.InsertHead(111);
    slink.Show();

    
    slink.RemoveAll(111);
    slink.Show();

    return 0;
}
#endif

