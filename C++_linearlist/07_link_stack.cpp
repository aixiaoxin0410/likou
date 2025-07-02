#include<iostream>
using namespace std;
#include <stack>

bool Priority(char ch, char topch)
{
    if( (ch =='*'|| ch == '/') && (topch == '+' || topch == '-') )
        return true;
    if(topch == '(' && ch != ')')
        return true;
    return false;
}

// 中缀表达式转后缀表达式
string MiddleToEndExpr(string expr)
{
    string result;
    stack<char> s;
    for(char ch : expr)
    {
        if(ch >='0' && ch<= '9')
        {
            result.push_back(ch);
        }
        else
        {
            if(s.empty() && ch=='(')
            {
                s.push(ch);
            }
            else
            {
                while(!s.empty())
                {
                    // 比较当前符号与栈顶符号优先级
                    char topch = s.top();
                    if(Priority(ch,topch))
                    {
                        s.push(ch);
                        break;
                    }
                    else
                    {
                        s.pop();
                        if(topch == '(')
                            break;
                        result.push_back(topch);
                    }
                }
            }
        }
    }

    while (!s.empty())
    {
        result.push_back(s.top());
        s.pop(); 
    }
    
    return result;
}

int main()
{
    cout << MiddleToEndExpr("(1+2)*(3+4)") << endl;
    // cout << MiddleToEndExpr("2+(4+6)/2+6/3") << endl;  
}


#if 0
// 链式栈
class LinkStack
{
public:
    LinkStack(): size_(0)
    {
        head = new Node();
    }
    ~LinkStack()
    {
        Node* p = head;
        while(p!=nullptr)
        {
            head = head->next;
            delete p;
            p = head;
        }
    }

    // 入栈 O(1)
    void push(int val)
    {
        Node* node = new Node(val);
        node->next = head->next;
        head->next = node;
        size_++;
    }

    // 出栈 O(1)
    void pop()
    {
        if(head->next == nullptr)
            throw "stack is empty!";
        Node *p = head->next;
        head->next = p->next;
        delete p;
        size_--;
    }

    // 获取栈顶元素
    int top() const
    {
        if(head->next == nullptr)
            throw "stack is empty!"; 
        return head->next->data;
    }

    // 判空
    bool empty() const
    {
        return head->next == nullptr;
    }

    // 返回栈元素个数 遍历一遍链表，记录节点个数 O(n)
    // 想达到 O(1)
    int size() const 
    {
        return size_;
    }

private:
    struct Node
    {
        Node(int data = 0)
            : data(data)
            , next(nullptr)
            {}
        int data;
        Node* next;
    };
    
    Node* head;
    int size_;
};


int main()
{
    int arr[] = {12,4,56,7,89,31,53,75};
    LinkStack ls;
    for(int v:arr)
    {
        ls.push(v);
    }

    int a = ls.size();
    cout << "栈的个数为：" << a << endl;
    
    while(!ls.empty())
    {
        cout << ls.top() << endl;
        ls.pop();
    }
    cout << endl;



    return 0;
}

#endif