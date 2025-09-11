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

    // 递归删除操作
    void remove(const T &val)
    {
        root_ = remove(root_,val);
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

    // 递归删除操作实现
    Node* remove(Node* node, const T &val)
    {
        if(node == nullptr)
            return nullptr;

        if(node->data_ == val) // 找到待删除节点
        {
            // 情况3
            if(node->left_ != nullptr && node->right_ != nullptr)
            {
                Node* pre = node->left_;
                while(pre->right_ != nullptr)
                {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;

                // 通过递归直接删除前驱节点
                node->left_ = remove(node->left_,pre->data_);
            }
            else
            {
                if(node->left_ != nullptr)
                {
                    // 删除节点后，把非空的左孩子返回，回溯时更新其父节点地址域
                    Node* left = node->left_;
                    delete node;
                    return left;
                }
                else if(node->right_ != nullptr)
                {
                    // 删除节点后，把非空的右孩子返回，回溯时更新其父节点地址域
                    Node* right = node->right_;
                    delete node;
                    return right;
                }
                else // 删除的是没有孩子的节点：叶子节点
                {
                    delete node;
                    return nullptr; // 回溯时更新其父节点地址域为nullptr
                }
            }
        }
        else if(comp_(node->data_,val))
        {
            node->right_ = remove(node->right_,val);
        }
        else
        {
            node->left_ = remove(node->left_,val);
        }
        return node; // 把当前节点返回给父节点，更新父节点相应的地址域
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
    bst.remove(58);
    bst.InOrder();
    return 0;
}
