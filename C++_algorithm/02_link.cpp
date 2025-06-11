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
};

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

    return 0;
}


