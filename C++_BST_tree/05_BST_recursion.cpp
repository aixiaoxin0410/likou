#include <iostream>
using namespace std;
#include <functional>  // 添加这个头文件

// BST树代码实现
template<typename T, typename Compare=less<T>>
class BSTree
{
public:
    BSTree()
        : root_(nullptr)
        {}
    ~BSTree(){}

    // 递归中序遍历操作
    void InOrder()
    {
        cout << "[递归]中序遍历：";
        InOrder(root_);
        cout << endl;
    }

    // 递归插入操作
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }

    // 递归查询操作
    bool query(const T &val)
    {
        return nullptr != query(root_,val);
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

    // 递归中序遍历的实现 LVR
    void InOrder(Node* node)
    {
        if(node != nullptr)
        {
            InOrder(node->left_); // 操作L
            cout << node->data_ << " "; // V
            InOrder(node->right_); // R
        }
    }  

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

    // 递归查询操作实现
    Node* query(Node* node, const T &val)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(node->data_ == val)
        {
            return node;
        }
        else if(comp_(node->data_,val))
        {
            return query(node->right_,val);
        }
        else
        {
            return query(node->left_,val);
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
    bst.InOrder();
    cout << bst.query(12) << endl;
    cout << endl;
    return 0;
}
