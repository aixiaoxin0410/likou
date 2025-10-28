#include <iostream>
using namespace std;

//红黑树代码
template<typename T> 
class RBTree
{
public:
    RBTree()
    : root_(nullptr)
    {}

    // 插入操作
    void insert(const T &val)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }

        Node* parent = nullptr;
        Node* cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ > val)
            {
                parent = cur;
                cur = cur->left_;
            }
            else if(cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                return;
            }   
        }

        // 设置当前节点的颜色和parent
        Node * node = new Node(val,parent,nullptr,nullptr,RED);
        if(parent->data_ > val)
        {
            parent->left_ = node;
        }
        else
        {
            parent->right_ = node;
        }

        // 如果新插入的红色节点，父节点也是红色，不满足红黑树性质，进行插入调整操作
        if(RED = color(parent))
        {
            FixAfterInsert(node);
        }
    }

private:
    // 节点颜色
    enum Color
    {
        BLACK,
        RED
    };

    struct Node
    {
        Node(T data = T(), Node* parent = nullptr, Node* left = nullptr
            , Node* right = nullptr, Color colar = BLACK)
        : data_(data)
        , left_(left)
        , right_(right_)
        , color_(colar)
        {}

        T data_;
        Node *left_;
        Node* right_;
        Node* parent_; // 指向当前父节点
        Color color_;
    };
    
    // 返回节点颜色
    Color color(Node* node)
    {
        return node == nullptr ? BLACK : node->color_;
    }

    // 设置节点的颜色
    void SetColor(Node * node, Color colar)
    {
        node->color_ = colar;
    }

    // 返回节点的右孩子
    Node* right(Node* node)
    {
        return node->right_;
    }

    // 返回节点的左孩子
    Node* left(Node* node)
    {
        return node->left_;
    }

    // 返回节点的父亲
    Node* parent(Node* node)
    {
        return node->parent_;
    }

    // 左旋转
    void LeftRotate(Node* node)
    {
        Node* child = node->right_;
        child->parent_ = node->parent_;
        if(node->parent_ == nullptr)
        {
            // 说明node本身是root节点
            root_ = child ;
        }
        else
        {
            if(node->parent_->left_ == node)
            {
                // node在父节点的左孩子
                node->parent_->left_ = child;
            }
            else
            {
                // node在父节点的右孩子
                node->parent_->right_ = child;
            }
        }

        node->right_ = child->left_;
        if(child->left_ != nullptr)
        {
            child->left_->parent_ = node;
        }

        child->left_ = node;
        node->parent_ = child;
    }

    // 右旋转
    void RightRotate(Node* node)
    {
        Node* child = node->left_;
        child->parent_ = node->parent_;
        if(node->parent_ == nullptr)
        {
            // 说明node本身是root节点
            root_ = child ;
        }
        else
        {
            if(node->parent_->left_ == node)
            {
                // node在父节点的左孩子
                node->parent_->left_ = child;
            }
            else
            {
                // node在父节点的右孩子
                node->parent_->right_ = child;
            }
        }

        node->left_ = child->right_;
        if(child->right_ != nullptr)
        {
            child->right_->parent_ = node;
        }

        child->right_= node;
        node->parent_ = child;
    }

    // 红黑树的插入调整操作
    void FixAfterInsert(Node* node)
    {
        // 如果当前红色节点的父节点也是红色，继续调整
        while(color(parent(node) == RED))
        {
            if(left(parent(parent(node))) == parent(node))
            {
                // 插入的节点在左子树当中
                Node* uncle = right(parent(parent(node)));
                // 情况一
                if(RED == color(uncle))
                {
                    SetColor(parent(node),RED);
                    SetColor(uncle,BLACK);
                    SetColor(parent(parent(node)),RED);
                    node = parent(parent(node)); // 继续调整

                }
                else
                {
                    // 先处理情况三
                    if(right(parent(node)) == node)
                    {
                        node = parent(node); // node指向的节点要和情况二一致
                        LeftRotate(parent(node));
                    }

                    // 统一处理情况二
                    SetColor(parent(node),BLACK);
                    SetColor(parent(parent(node)),RED);
                    RightRotate(parent(parent(node)));
                    break; // 调整已经完成
                }
            }
            else
            {
                // 插入的节点在右子树当中
                Node* uncle = left(parent(parent(node)));
                // 情况一
                if(RED == color(uncle))
                {
                    SetColor(parent(node),RED);
                    SetColor(uncle,BLACK);
                    SetColor(parent(parent(node)),RED);
                    node = parent(parent(node)); // 继续调整

                }
                else
                {
                    // 先处理情况三
                    if(left(parent(node)) == node)
                    {
                        node = parent(node); // node指向的节点要和情况二一致
                        RightRotate(parent(node));
                    }

                    // 统一处理情况二
                    SetColor(parent(node),BLACK);
                    SetColor(parent(parent(node)),RED);
                    LeftRotate(parent(parent(node)));
                    break; // 调整已经完成
                }
            }
        }

        // 此处强制root为黑色节点
        SetColor(root_,BLACK);

    }


    Node* root_;
};

int main()
{
    return 0;
}