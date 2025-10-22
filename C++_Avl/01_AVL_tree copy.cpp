// #include"pch.h"
#include<iostream>
using namespace std;
#include<cmath>

template <typename T>
class AvlTree
{
public:
    AvlTree()
        : root_(nullptr)
        {}

    // AVL树的插入操作
    void insert(const T& val)
    {
        root_ = insert(root_,val);
    }

private:

    // 定义AVL树节点类型
    struct Node
    {
        Node(T data = T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1)
            {}
        T data_;
        Node* left_;
        Node* right_;
        int height_; // 记录节点的高度值
    };
    
    // 返回节点的高度值
    int height(Node* node)
    {
        return node == nullptr ? 0 : node->height_;
    }

    // 右旋转操作 以参数Node为轴做右旋转操作，并把新的根节点返回
    Node* RightRotate(Node* node)
    {
        // 节点旋转
        Node* child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;

        // 高度更新 node child
        node->height_ = max(height(node->left_),height(node->right_)) + 1;
        child->height_ = max(height(child->left_),height(child->right_)) + 1;
        // 返回旋转后的子树新的根节点
        return child; 
    }

    // 左旋转操作 以参数Node为轴做左旋转操作，并把新的根节点返回
    Node* LeftRotate(Node* node)
    {
        // 节点旋转
        Node* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        // 高度更新 node child
        node->height_ = max(height(node->left_),height(node->right_)) + 1;
        child->height_ = max(height(child->left_),height(child->right_)) + 1;
        // 返回旋转后的子树新的根节点
        return child; 
    }

    // 左平衡操作，以参数Node为轴做左-右旋转操作，并把新的根节点返回
    Node* RightBalance(Node* node)
    {
        node->left_ = LeftRotate(node->left_);
        return RightRotate(node);
    }

    // 右平衡操作，以参数Node为轴做右-左旋转操作，并把新的根节点返回
    Node* LeftBalance(Node* node)
    {
        node->right_ = RightRotate(node->right_);
        return LeftRotate(node);
    }

        // AVL树的插入操作
    Node* insert(Node* node, const T& val)
    {
        if(node == nullptr) // 递归结束，找到插入的位置了
        {
            return new Node(val);
        }
        if(node->data_ > val)
        {
            node->left_ = insert(node->left_,val);
            // 添加1 在递归回溯时判断节点是否失衡，node的左子树太高，node失衡了
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    // 节点失衡，由于左子树的左子树太高
                    node = RightRotate(node);
                }
                else
                {
                    // 节点失衡，由于左子树的右子树太高
                    node = LeftBalance(node); 
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = insert(node->right_,val);
            // 添加2 在递归回溯时判断节点是否失衡，node的右子树太高，node失衡了
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    // 节点失衡，由于右子树的右子树太高
                    node = LeftRotate(node);
                }
                else
                {
                    // 节点失衡，由于右子树的左子树太高
                    node = RightBalance(node); 
                }
            }
        }
        else
        {
            ; // 找到相同节点，不用再往下递归了，直接向上回溯
        }

        // 添加3 因为子树中增加了新的节点 在递归回溯时检测更新节点高度
        node->height_ = max(height(node->left_),height(node->right_)) + 1;

        return node;
    }

    Node* root_; // 指向根节点
};

int main()
{
    AvlTree<int> avl;
    for(int i =1;i<=10;i++)
    {
        avl.insert(i);
    }
    
    return 0;
}