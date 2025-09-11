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

    // 非递归插入操作
    void n_insert(const T &val)
    {
        // 树为空，生成根节点
        if(root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }

        // 搜索合适的插入位置，记录父节点的位置
        Node* parent = nullptr;
        Node* cur = root_;
        while(cur!= nullptr)
        {
            if(cur->data_ == val) 
            {
                // 不插入元素相同的值
                return;
            }
            else if(comp_(cur->data_,val)) // 小于关系
            {
                parent = cur;
                cur = cur->right_;
            }

            else
            {   
                parent = cur;
                cur = cur->left_;
            }
        }

        // 把新节点插入到parent节点的孩子上
        if(comp_(parent->data_,val)) // 小于关系
        {
            parent->right_ = new Node(val);
        }
        else
        {
            parent->left_= new Node(val);
        }
    }

    // 非递归删除操作
    void n_remove(const T& val)
    {
        if(root_ == nullptr)
        {
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;
        while(cur!= nullptr)
        {
            if(cur->data_ == val) 
            {
                break; // 找到待删除节点
            }
            else if(comp_(cur->data_,val)) // 小于关系
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {   
                parent = cur;
                cur = cur->left_;
            }
        }

        // 没找到待删除节点
        if(cur == nullptr)
        {
            return;
        }

        // 情况3
        if(cur->left_!=nullptr && cur->right_!=nullptr)
        {
            parent = cur;
            Node* pre = cur->left_;
            while (pre->right_ !=nullptr)
            {
                parent = pre;
                pre = pre->right_;
            }
            
            cur->data_ = pre->data_;
            cur = pre; // 让cur指向前驱节点，转化成情况1，2
        }

        // cur指向删除节点，parent指向其父节点，统一处理情况1或者2
        Node* child = cur->left_;
        if(child == nullptr)
        {
            child = cur->right_;
        }

        if(parent == nullptr) // 特殊情况：表示删除的是根节点
        {
            root_ = child;
        }

        // 把待删除节点的孩子（nullptr或者不空）写入其父节点相应地址域中
        if(parent->left_ == cur)
        {
            parent->left_ = child;
        }
        else
        {
            parent->right_ = child;
        }

        delete cur; // 删除当前节点
    }

    // 非递归查询
    bool n_query(const T& val)
    {
        Node* cur = root_;
        while(cur!= nullptr)
        {
            if(cur->data_ == val)
            {
                return true;
            }
            else if(comp_(cur->data_,val))
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }

        return false;
    }

    // 递归前序遍历操作
    void PreOrder()
    {
        cout << "[递归]前序遍历：";
        PreOrder(root_);
        cout << endl;
    }

    // 递归中序遍历操作
    void InOrder()
    {
        cout << "[递归]中序遍历：";
        InOrder(root_);
        cout << endl;
    }

    // 递归后序遍历操作
    void PostOrder()
    {
        cout << "[递归]后序遍历：";
        PostOrder(root_);
        cout << endl;
    }

    // 递归层序遍历操作
    void LevelOrder()
    {
        cout << "[递归]层序遍历：";
        int h = high(); // 树的层数
        for(int i = 0 ; i < h ; ++i)
        {
            LevelOrder(root_,i); // 递归调用树的层数次
        }
        cout << endl;
    }    

    // 递归求二叉树层数
    int high()
    {
        return high(root_);
    }

    // 递归求二叉树节点个数
    int number()
    {
        return number(root_);
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
    
    // 递归前序遍历的实现 VLR
    void PreOrder(Node* node)
    {
        if(node != nullptr)
        {
            cout << node->data_ << " "; //操作 V
            PreOrder(node->left_); // L
            PreOrder(node->right_); // R
        }
    }

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

    // 递归后序遍历的实现 LRV
    void PostOrder(Node* node)
    {
        if(node != nullptr)
        {
            PostOrder(node->left_); // L
            PostOrder(node->right_); // R
            cout << node->data_ << " "; // V
        }
    }

    // 递归层序遍历操作的实现
    void LevelOrder(Node* node, int i)
    {
        if(node == nullptr)
        {
            return;
        }        
        
        if(i == 0)
        {
            cout << node->data_ << " ";
            return;
        }
        LevelOrder(node->left_, i - 1);
        LevelOrder(node->right_, i - 1);
    } 

    // 递归求二叉树层数 求以node为根节点的子树的高度并返回高度值
    int high(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left = high(node->left_);
        int right = high(node->right_);

        return left > right ? left + 1 : right + 1;
    }

    // 递归求二叉树节点个数的实现
    int number(Node* node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        int left = number(node->left_);
        int right = number(node->right_);

        return left + right + 1;
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
        bst.n_insert(v);
    }

    // cout << bst.n_query(12) << endl;
    // bst.n_insert(12);
    // cout << bst.n_query(12) << endl;
    // bst.n_remove(12);
    // bst.n_remove(24);
    // bst.n_remove(58);
    // cout << bst.n_query(12) << endl;
    // bst.PreOrder();
    // bst.InOrder();
    // bst.PostOrder();
    bst.LevelOrder();
    cout << bst.high() << endl;
    cout << bst.number() << endl;

    return 0;
}
