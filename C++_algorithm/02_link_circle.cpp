#include<iostream>
using namespace std;

class CircleLink
{
public:
    CircleLink()
    {
        head = new Node();
        head = tail;
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
    return 0;
}



