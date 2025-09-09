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
            if(!comp_(cur->data_,val)) // 大于关系
            {
                parent = cur;
                cur = cur->left_;
            }
            else if(comp_(cur->data_,val)) // 小于关系
            {
                parent = cur;
                cur = cur->right_;
            }
            // 不插入元素相同的值
            else
            {   
                return;
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

    bst.n_insert(12);
    return 0;
}
