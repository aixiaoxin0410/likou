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

    Node* root_;
};

int main()
{
    return 0;
}