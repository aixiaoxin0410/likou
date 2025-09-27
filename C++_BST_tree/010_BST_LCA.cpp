#include <iostream>
using namespace std;
#include <functional>  // 添加这个头文件
#include<stack>
#include<queue>
#include<vector>

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

    // 非递归后序排序操作 LRV -> VRL
    void n_PostOrder()
    {
        cout << "[非递归]后序遍历：";    
        if(root_ == nullptr)
        {
            return;
        }   
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        while(!s1.empty())
        {
            Node* top = s1.top();
            s1.pop();
            s2.push(top);
            if(top->left_ != nullptr)
            {
                s1.push(top->left_);
            }
            if(top->right_ != nullptr)
            {
                s1.push(top->right_);
            }       
        }
        
    }

    // 非递归层序排序遍历操作
    void n_LevelOrder()
    {
        cout << "[非递归]层序遍历：";  
        if(root_ == nullptr)
        {
            return;
        }
        queue<Node*> que;
        que.push(root_);
        while (!que.empty())
        {
            Node* front = que.front();
            que.pop();
            cout << front->data_ << " ";
            if(front->left_ != nullptr)
            {
                que.push(front->left_);
            }
            if(front->right_ != nullptr)
            {
                que.push(front->right_);
            }
        }
    }

    // 求满足区间的元素值[i, j]
    void FindValues(vector<T> & vec, int i , int j)
    {
        FindValues(root_,vec,i,j);
    }

    // 判断一颗二叉树是否是BST树
    bool IsBSTree_error()
    {
        return IsBSTree_error(root_);
    }

    bool IsBSTree_true()
    {
        Node* pre = nullptr;
        return IsBSTree_true(root_,pre);
    }

    void test() // 测试是否是BST树
    {
        BSTree<T> bst;
        bst.root_ = new Node(40);
        Node* node1 = new Node(20);
        Node* node2 = new Node(60);
        Node* node3 = new Node(30);
        Node* node4 = new Node(80);
        bst.root_->left_ = node1;
        bst.root_->right_ = node2;
        node2->left_ = node3;
        node2->right_ = node4;

        // cout << bst.IsBSTree_error() << endl;
        cout << bst.IsBSTree_true() << endl;
    }

    // 测试子树判断问题
    void test01()
    {
        int arr[] = {58,24,67,0,34,62,69,5,41,64,78};
        BSTree<int> bst_f;
        for(auto v:arr)
        {
            bst_f.insert(v);
        }

        BSTree<T> bst;
        bst.root_ = new Node(67);
        Node* node1 = new Node(62);
        Node* node2 = new Node(69);
        Node* node3 = new Node(60);
        bst.root_->left_ = node1;
        bst.root_->right_ = node2;
        // node1->left_ = node3;  
        cout << bst_f.IsChildTree(bst) << endl;
    }

    // 测试LCA问题
    void test02()
    {
        int arr[] = {58,24,67,0,34,62,69,5,41,64,78};
        BSTree<int> bst;
        for(auto v:arr)
        {
            bst.insert(v);
        }

        cout << bst.GetLCA(64,62) << endl;
    }

    // 判断子树问题
    bool IsChildTree(BSTree<T, Compare> & child  )
    {
        // 在当前二叉树上找child的根节点
        if(child.root_ == nullptr)
        {
            return true;
        }
        
        Node* cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ == child.root_->data_)
            {
                break;
            }
            else if(comp_(cur->data_,child.root_->data_))
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }
        if(cur == nullptr)
        {
            return false;
        }

        return IsChildTree(cur, child.root_);
    }

    // 最近公共祖先节点
    int GetLCA(int val1, int val2)
    {
        Node* node = GetLCA(root_,val1,val2);
        if(node == nullptr)
        {
            throw "no LCA！";
        }
        else
        {
            return node->data_;
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

    // 求满足区间的元素值的实现[i, j]
    void FindValues(Node* node,vector<T> & vec, int i , int j)
    {
        if(node != nullptr)
        {
            // 在当前节点的左子树中搜索
            if(node->data_ > i)
            {
                FindValues(node->left_,vec,i,j);
            }
            if(node->data_ >= i && node->data_ <= j)
            {
                vec.push_back(node->data_);
            }
            if(node->data_ < j)
            {
                // 在当前节点的右子树中搜索
                FindValues(node->right_,vec,i,j);
            }
        }
    }

    // 判断一颗二叉树是否是BST树操作实现
    bool IsBSTree_error(Node* node) //错误的代码
    {
        if(node == nullptr)
        {
            return true;
        }
        // V
        if(node->left_ != nullptr && comp_(node->data_,node->left_->data_))
        {
            return false;
        }
        if(node->right_ != nullptr && comp_(node->right_->data_,node->data_))
        {
            return false;
        }
        return IsBSTree_error(node->left_); // L 判断当前节点的左子树    
        return IsBSTree_error(node->right_); // R 判断当前节点的右子树
    }

    // 判断一颗二叉树是否是BST树实现，利用BST树中序遍历是一个升序的特点
    bool IsBSTree_true(Node* node, Node*& pre) 
    {
        if(node == nullptr)
        {
            return true;
        }
        if(!IsBSTree_true(node->left_,pre)) // L 主要判断递归结束的条件
        {
            return false;
        } 
        // V
        if(pre != nullptr)
        {
            if(comp_(node->data_,pre->data_)) // 主要判断递归结束的条件
            {
                return false;
            }
        }
        pre = node; // 更新中序遍历的前驱节点

        return IsBSTree_true(node->right_,pre); // R
    }

    // 判断子树问题实现
    bool IsChildTree(Node* father, Node* child)
    {
        if(father == nullptr && child == nullptr)
        {
            return true;
        }
        if(father == nullptr) // 子树里面有的节点，当前二叉树没有
        {
            return false;
        }
        if(child == nullptr)
        {
            return true;
        }

        // 判断值不相同
        if(father->data_ != child->data_) // V
        {
            return false;
        }

        return IsChildTree(father->left_,child->left_) // L
            && IsChildTree(father->right_,child->right_); // R
    }

    // 最近公共祖先节点的实现
    Node* GetLCA(Node* node, int val1, int val2)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        if(comp_(node->data_,val1) && comp_(node->data_,val2))
        {
            return GetLCA(node->right_,val1,val2);
        }
        else if(comp_(val1,node->data_) && comp_(val2,node->data_))
        {
            return GetLCA(node->left_,val1,val2);
        }
        else
        {
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
    bst.n_LevelOrder();
    cout << endl;

    vector<int> vec;
    bst.FindValues(vec,10,60);
    for(auto v:vec)
    {
        cout << v << " ";
    }
    cout << endl;

    // cout << bst.IsBSTree_error() << endl;
    // bst.test();
    // bst.test01();
    bst.test02();

    return 0;
}
