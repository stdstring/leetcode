#include <algorithm>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
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

using CommonLib::Codec;

namespace BalancedBinaryTreeTask
{

TEST(BalancedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isBalanced(Codec::createTree("[3,9,20,null,null,15,7]").get()));
    ASSERT_EQ(false, solution.isBalanced(Codec::createTree("[1,2,2,3,3,null,null,4,4]").get()));
}

}