#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

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

using CommonLib::Codec;
using CommonLib::checkTreeNextLinks;

namespace PopulatingNextRightPointersInEachNodeTask
{

TEST(PopulatingNextRightPointersInEachNodeTaskTests, Examples)
{
    Solution solution;
    checkTreeNextLinks({{1}, {2, 3}, {4, 5, 6, 7}}, solution.connect(Codec::createTree("[1,2,3,4,5,6,7]").get()));
}

}