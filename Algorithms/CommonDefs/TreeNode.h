#pragma once

#include <memory>

#include "gtest/gtest.h"

namespace CommonDefs
{

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next;

    TreeNode() : val(0), left(nullptr), right(nullptr), next(nullptr)
    {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr)
    {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), next(nullptr)
    {
    }

    TreeNode(int x, int leftValue, TreeNode* right) : val(x), left(new TreeNode(leftValue)), right(right), next(nullptr)
    {
    }

    TreeNode(int x, TreeNode* left, int rightValue) : val(x), left(left), right(new TreeNode(rightValue)), next(nullptr)
    {
    }

    TreeNode(int x, int leftValue, int rightValue) : val(x), left(new TreeNode(leftValue)), right(new TreeNode(rightValue)), next(nullptr)
    {
    }
};


void deleteTree(TreeNode* root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

std::shared_ptr<TreeNode> createTreeHolder(TreeNode* root)
{
    return std::shared_ptr<TreeNode>(root, deleteTree);
}

void checkTree(TreeNode* expected, TreeNode* actual)
{
    if (expected == nullptr)
    {
        ASSERT_TRUE(actual == nullptr);
        return;
    }
    ASSERT_EQ(expected->val, actual->val);
    checkTree(expected->left, actual->left);
    checkTree(expected->right, actual->right);
}

void checkAndDeleteTree(TreeNode* expected, TreeNode* actual)
{
    checkTree(expected, actual);
    deleteTree(actual);
}

}