#include <iostream>
using namespace std;
#include <functional>  // 添加这个头文件
#include<stack>

// BST树代码实现
template<typename T, typename Compare=less<T>>
class BSTree
{
public:
    BSTree()
        : root_(nullptr)
        {}
    ~BSTree(){}

    // 递归插入操作
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }

    // 非递归前序遍历操作 VLR
    void n_PreOrder()
    {
        cout << "[非递归]前序遍历：";
        if(root_ == nullptr)
        {
            return;
        }
        stack<Node*> s;
        s.push(root_);
        while (!s.empty())
        {   
            Node* top = s.top();
            s.pop();
            cout << top->data_ << " "; // V
            if(top->right_ != nullptr)
            {
                s.push(top->right_); // R
            }
            if(top->left_ != nullptr)
            {
                s.push(top->left_); // L
            }
        }
        cout << endl; 
    }

    // 非递归中序遍历操作 LVR
    void n_InOrder()
    {
        cout << "[非递归]中序遍历：";
        if(root_ == nullptr)
        {
            return;
        }
        stack<Node*> s;
        Node* cur = root_;
        while (!s.empty() || cur != nullptr)
        { 
            if(cur != nullptr)  
            {
                s.push(cur);
                cur = cur->left_;
            }
            else
            {
                Node* top = s.top();
                s.pop();
                cout << top->data_ << " "; 
                cur = top->right_;
            }
        }
        cout << endl; 
    }

private:
    struct Node
    {
        Node(T data = T())
            : data_(data)
            , right_(nullptr)
            , left_(nullptr)
            {}
        T data_; // 数据域
        Node* right_; // 左孩子域
        Node* left_; // 右孩子域
    };

    // 递归插入操作实现
    Node* insert(Node* node, const T &val)
    {
        if(node == nullptr)
        {
            // 递归结束，找到插入val的位置，生成新节点并返回其节点地址
            return new Node(val);
        }

        if(node->data_ == val)
        {
            return node;
        }
        else if(comp_(node->data_,val))
        {
            node->right_ = insert(node->right_,val);
            return node;
        }
        else
        {
            node->left_ = insert(node->left_,val);
            return node;
        }
    } 

    Node* root_; // 指向BST树的根节点
    Compare comp_; // 定义一个函数对象
};

int main()
{
    int arr[] = {58,24,67,0,34,62,69,5,41,64,78};
    BSTree<int> bst;
    for(auto v:arr)
    {
        bst.insert(v);
    }

    bst.n_PreOrder();
    bst.n_InOrder();
    return 0;
}
