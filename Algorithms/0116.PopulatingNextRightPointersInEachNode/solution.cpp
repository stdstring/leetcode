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
using CommonDefs::checkTreeNextLinks;

namespace PopulatingNextRightPointersInEachNodeTask
{

TEST(PopulatingNextRightPointersInEachNodeTaskTests, Examples)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 6, 7}}, solution.connect(createTreeHolder(new TreeNode(1, new TreeNode(2, 4, 5), new TreeNode(3, 6, 7))).get()));
}

}