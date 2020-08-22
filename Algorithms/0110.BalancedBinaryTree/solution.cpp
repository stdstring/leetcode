#include <algorithm>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution {
public:
    bool isBalanced(TreeNode* root) const
    {
        size_t treeSize = 0;
        return checkTree(root, treeSize);
    }

private:
    bool checkTree(TreeNode* root, size_t &treeSize) const
    {
        treeSize = 0;
        if (root == nullptr)
            return true;
        size_t leftSize = 0;
        size_t rightSize = 0;
        if (!checkTree(root->left, leftSize))
            return false;
        if (!checkTree(root->right, rightSize))
            return false;
        if (leftSize > (rightSize + 1) || rightSize > (leftSize + 1))
            return false;
        treeSize = 1 + std::max(leftSize, rightSize);
        return true;
    }
};

}

using CommonDefs::createTreeHolder;

namespace BalancedBinaryTreeTask
{

TEST(BalancedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isBalanced(createTreeHolder(new TreeNode(3, 9, new TreeNode(20, 15, 7))).get()));
    ASSERT_EQ(false, solution.isBalanced(createTreeHolder(new TreeNode(1, new TreeNode(2, new TreeNode(3, 4, 4), 3), 2)).get()));
}

}