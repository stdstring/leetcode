#pragma once

namespace CommonLib
{

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next;

    TreeNode();
    explicit TreeNode(int x);
    TreeNode(int x, TreeNode* left, TreeNode* right);
    TreeNode(int x, int leftValue, TreeNode* right);
    TreeNode(int x, TreeNode* left, int rightValue);
    TreeNode(int x, int leftValue, int rightValue);
};

}