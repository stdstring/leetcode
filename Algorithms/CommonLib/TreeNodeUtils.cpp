#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "TreeNode.h"
#include "TreeNodeUtils.h"

namespace
{

void deleteTree(CommonLib::TreeNode* root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

}

std::shared_ptr<CommonLib::TreeNode> CommonLib::createTreeHolder(TreeNode* root)
{
    return std::shared_ptr<TreeNode>(root, deleteTree);
}

void CommonLib::checkTree(TreeNode* expected, TreeNode* actual)
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

void CommonLib::checkAndDeleteTree(TreeNode* expected, TreeNode* actual)
{
    checkTree(expected, actual);
    deleteTree(actual);
}

void CommonLib::checkTreeNextLinks(std::vector<std::vector<int>> const &nextLinksLayers, TreeNode* root)
{
    TreeNode* leader = root;
    for (std::vector<int> const &layer : nextLinksLayers)
    {
        ASSERT_NE(nullptr, leader);
        TreeNode* current = leader;
        for (int value : layer)
        {
            ASSERT_NE(nullptr, current);
            ASSERT_EQ(value, current->val);
            current = current->next;
        }
        ASSERT_EQ(nullptr, current);
        // move to next leader
        while (leader != nullptr)
        {
            if (leader->left != nullptr)
            {
                leader = leader->left;
                break;
            }
            if (leader->right != nullptr)
            {
                leader = leader->right;
                break;
            }
            leader = leader->next;
        }
    }
}