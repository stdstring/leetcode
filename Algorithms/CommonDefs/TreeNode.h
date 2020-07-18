#pragma once

#include <memory>

#include "gtest/gtest.h"

namespace CommonDefs
{

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr)
    {
    }

    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {
    }

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right)
    {
    }
};


void deleteTree(TreeNode *root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

std::shared_ptr<TreeNode> createTreeHolder(TreeNode *root)
{
    return std::shared_ptr<TreeNode>(root, deleteTree);
}

void checkTree(TreeNode *expected, TreeNode *actual)
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

void checkAndDeleteTree(TreeNode *expected, TreeNode *actual)
{
    checkTree(expected, actual);
    deleteTree(actual);
}

}