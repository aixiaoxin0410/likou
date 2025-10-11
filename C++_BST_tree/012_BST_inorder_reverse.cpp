#include <iostream>
using namespace std;
#include <functional>  // 添加这个头文件
#include<stack>
#include<queue>
#include<vector>
#include<cmath>

// BST树代码实现
template<typename T, typename Compare=less<T>>
class BSTree
{
public:
    // 初始化根节点和函数对象
    BSTree(Compare comp = Compare())
        : root_(nullptr)
        , comp_(comp)
        {}

    // 层序遍历思想释放BST树所有节点资源
    ~BSTree()
    {
        if(root_ != nullptr)
        {
            queue<Node*> s;
            s.push(root_);
            while(!s.empty())
            {
                Node* front = s.front();
                s.pop();

                if(front->left_ != nullptr)
                {
                    s.push(front->left_);
                }
                if(front->right_!= nullptr)
                {
                    s.push(front->right_);
                }
                delete front;
            }
        }
    }

    // 递归插入操作
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }

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

    // 镜像翻转
    void mirror01()
    {
        mirror01(root_);
    }

    // 测试LCA问题
    void test03()
    {
        int arr[] = {58,24,67,0,34,62,69,5,41,64,78};
        BSTree<int> bst;
        for(auto v:arr)
        {
            bst.insert(v);
        }

        bst.n_InOrder();
        bst.mirror01();
        bst.n_InOrder();
    }

    // 二叉树镜像对称问题
    bool mirror02()
    {
        if(root_ == nullptr)
        {
            return true;
        }
        return mirror02(root_->left_, root_->right_);
    }

    void test04() // 测试镜像对称问题
    {
        BSTree<T> bst;
        bst.root_ = new Node(40);
        Node* node1 = new Node(20);
        Node* node2 = new Node(20);
        Node* node3 = new Node(10);
        Node* node4 = new Node(15);
        Node* node5 = new Node(15);
        Node* node6 = new Node(10);
        bst.root_->left_ = node1;
        bst.root_->right_ = node2;
        node1->left_ = node3;
        node1->right_ = node4;
        node2->left_ = node5;
        node2->right_ = node6;

        cout << bst.mirror02() << endl;
    }

    // 重建二叉树
    void rebuild(int pre[], int i, int j, int in[], int m, int n)
    {
        root_ = _rebuild(pre, i, j, in, m, n);
    }

    void test05()
    {
        BSTree<T> bst;
        int pre[] = {58,24,0,5,34,41,67,62,64,69,78};
        int in[] = {0,5,24,34,41,58,62,64,67,69,78};
        bst.rebuild(pre,0,10,in,0,10);
        bst.n_PreOrder();
        bst.n_InOrder();           
    }
    
    // 递归求二叉树层数
    int high()
    {
        return high(root_);
    }

    // 判断平衡树
    // bool IsBalance()
    // {
    //     return IsBalance(root_, l);
    // }

    // 判断平衡树
    bool IsBalance()
    {
        int l = 0;
        bool flag = true;
        IsBalance02(root_, l, flag);
        return flag;
    }

    // 求中序倒数第K个节点
    int GetVal(int k)
    {
        Node* node = GetVal(root_, k);
        if(node == nullptr)
        {
            string err = "no No.";
            err += k;
            throw err;
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

    // 镜像翻转代码实现
    void mirror01(Node* node)
    {
        if(node == nullptr)
            return;

        // V
        Node* tmp = node->left_;
        node->left_ = node->right_;
        node->right_ = tmp;

        mirror01(node->left_); // L
        mirror01(node->right_); // R
    }

    // 二叉树镜像对称问题
    bool mirror02(Node* node1, Node* node2) 
    {
        if(node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        if(node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        if(node1->data_ != node2->data_)
        {
            return false;
        }
        return mirror02(node1->left_,node2->right_) && 
        mirror02(node1->right_,node2->left_);
    }

    // 重建二叉树递归实现
    Node* _rebuild(int pre[], int i, int j, int in[], int m, int n)
    {
        if(i > j || m > n)
        {
            return nullptr;
        }

        // 创建当前子树的节点
        Node* node = new Node(pre[i]); // 拿前序的第一个数字创建子树根节点
        for(int k = m; k <= n; k++)
        {
            if(pre[i] == in[k]) // 在中序遍历中找子树根节点的下标k
            {
                node->left_ = _rebuild(pre, i+1, i+k-m, in, m, k-1);
                node->right_ = _rebuild(pre,i+k-m+1, j,in, k+1,n);
                return node;
            }
        }
        return node;
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

    // 判断平衡树代码实现 (效率比较低)
    bool IsBalance(Node* node)
    {
        if(node == nullptr)
        {
            return true;
        }
        if(!IsBalance(node->left_)) // L
        {
            return false;
        }
        if(!IsBalance(node->right_)) // R
        {
            return false;
        }

        int left = high(node->left_);
        int right = high(node->right_);
        return abs(left - right) <= 1;
    }

    // 判断平衡树 效率高 递归过程中，记录节点的高度值 返回节点高度值
    int IsBalance02(Node* node , int l, bool & flag)
    {
        if(node == nullptr)
        {
            return l;
        }

        int left = IsBalance02(node->left_, l+1, flag);
        if(!flag)
        {
            return left;
        }
        int right = IsBalance02(node->right_, l+1, flag);
        if(!flag)
        {
            return right;
        }
        if(abs(left - right) > 1) // 节点失衡了
        {
            flag = false;
        }   
        return max(left,right);
    }

    // 求中序倒数第K个节点代码实现
    int i = 1;
    Node* GetVal(Node* node, int k)
    {
        if(node == nullptr)
        {
            return nullptr;
        }

        Node* left = GetVal(node->right_, k); // R
        if(left != nullptr)
        {
            return left;
        }
        // V
        if(i++ == k) // 在RVL的顺序下，找到正数的第k个元素
        {
            return node;
        }
        return GetVal(node->left_, k); // L
    }

    Node* root_; // 指向BST树的根节点
    Compare comp_; // 定义一个函数对象
};

int main()
{
    using Elm = pair<int, string>;
    using Functor = function<bool(pair<int, string>,pair<int, string>)>;
    BSTree<Elm,Functor> bst ([](Elm p1,Elm p2)->bool
    {
        return p1.first > p2.first;
    });
        

    // int arr[] = {58,24,67,0,34,62,69,5,41,64,78};
    // BSTree<int> bst;
    // for(auto v:arr)
    // {
    //     bst.insert(v);
    // }

    // cout << bst.IsBalance() << endl;
    // bst.insert(12);
    // cout << bst.IsBalance() << endl;  

    // bst.n_InOrder();
    // cout << bst.GetVal(3) << endl;

    // bst.n_PreOrder();
    // bst.n_InOrder();
    // bst.n_LevelOrder();
    // bst.n_PostOrder();
    // cout << endl;

    // vector<int> vec;
    // bst.FindValues(vec,10,60);
    // for(auto v:vec)
    // {
    //     cout << v << " ";
    // }
    // cout << endl;

    // cout << bst.IsBSTree_error() << endl;
    // bst.test();
    // bst.test01();
    // bst.test02();

    // bst.test03();
    // bst.test04();
    // bst.test05();

    return 0;
}
