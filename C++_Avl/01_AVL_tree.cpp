// #include"pch.h"
#include<iostream>
using namespace std;
#include<cmath>

template <typename T>
class AvlTree
{
public:

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
    Node* leftBalance(Node* node)
    {
        node->right_ = RightRotate(node->right_);
        return LeftRotate(node);
    }

    Node* root_; // 指向根节点
};

int main()
{
    return 0;
}