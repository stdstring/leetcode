#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* connect(TreeNode* root)
    {
        if (root != nullptr)
            connectImpl(root);
        return root;
    }

private:
    void connectImpl(TreeNode* current)
    {
        if (current->left != nullptr)
            current->left->next = current->right;
        if (current->right != nullptr)
            current->right->next = current->next != nullptr ? current->next->left : nullptr;
        if (current->left != nullptr)
            connectImpl(current->left);
        if (current->right != nullptr)
            connectImpl(current->right);
    }
};

}

using CommonDefs::createTreeHolder;

namespace PopulatingNextRightPointersInEachNodeTask
{

void checkTreeNextLinks(std::vector<std::vector<int>> const &layers, TreeNode* root)
{
    TreeNode* leader = root;
    for (std::vector<int> const &layer : layers)
    {
        TreeNode* current = leader;
        for (int value : layer)
        {
            ASSERT_NE(nullptr, current);
            ASSERT_EQ(value, current->val);
            current = current->next;
        }
        ASSERT_EQ(nullptr, current);
        leader = leader->left;
    }
}

TEST(PopulatingNextRightPointersInEachNodeTaskTests, Examples)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 6, 7}}, solution.connect(createTreeHolder(new TreeNode(1, new TreeNode(2, 4, 5), new TreeNode(3, 6, 7))).get()));
}

}