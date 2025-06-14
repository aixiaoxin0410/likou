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
            delete p;
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
    friend bool GetLastKNode(Slink &slink, int k , int &val);
    friend void MergeLink(Slink &slink1, Slink &slink2);
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

// 单链表倒数第k个节点
bool GetLastKNode(Slink &slink, int k , int &val)
{
    Node* head = slink.head;
    Node* pre = head;
    Node* p = head;

    if(k<1)
    {
        return false;
    }

    for(int i = 0; i<k; i++)
    {
        p = p->next;
        if(p == nullptr)
        {
            return false;
        }
    }

    while(p!= nullptr)
    {
        pre = pre->next;
        p = p->next;
    }

    val = pre->data;
    return true;
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
    }
    slink.Show();

    ReverseLink(slink);
    slink.Show();

    int val;
    int k = 0;
    if(GetLastKNode(slink, k, val))
    {
        cout << "倒数第" << k << "个节点的数值为：" << val;
    }
}
#endif

// 合并两个有序的单链表
void MergeLink(Slink &slink1, Slink &slink2)
{
    Node* last = slink1.head;
    Node* p = slink1.head->next;
    Node* q = slink2.head->next;
    slink2.head->next = nullptr; // 不加这句代码，析构函数会出错的。
                                //  因为这里链表2的head没有和原来的第一个节点断联，他同时指向两个数据

    while(p!=nullptr && q!=nullptr)
    {
        if(q->data < p->data)
        {
            last->next = q;
            q = q->next;
            last = last->next;
        }
        else
        {
            last->next = p;
            p = p->next;
            last = last->next;
        }
    }

    if(q == nullptr)
    {
        last->next = p;
    }

    if(p == nullptr)
    {
        last->next = q;
    }
}

int main()
{
    int arr1[] = {25, 37, 52, 78};
    int arr2[] = {13, 23, 40, 56, 84, 95, 106};

    Slink slink1;
    Slink slink2;

    for(int v:arr1)
    {
        slink1.InsertTail(v);    
    }

    for(int v:arr2)
    {
        slink2.InsertTail(v);    
    }

    slink1.Show();
    slink2.Show();

    MergeLink(slink1,slink2);
    slink1.Show();
    slink2.Show(); 
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

