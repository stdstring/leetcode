#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int goodNodes(TreeNode* root) const
    {
        return static_cast<int>(goodNodes(root, INT_MIN));
    }

private:
    size_t goodNodes(TreeNode* root, int maxValue) const
    {
        const size_t leftGoodNodes = root->left == nullptr ? 0 : goodNodes(root->left, std::max(maxValue, root->val));
        const size_t rightGoodNodes = root->right == nullptr ? 0 : goodNodes(root->right, std::max(maxValue, root->val));
        return leftGoodNodes + rightGoodNodes + (root->val >= maxValue ? 1 : 0);
    }
};

}

using CommonLib::Codec;

namespace CountGoodNodesInBinaryTreeTask
{

TEST(CountGoodNodesInBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.goodNodes(Codec::createTree("[3,1,4,3,null,1,5]").get()));
    ASSERT_EQ(3, solution.goodNodes(Codec::createTree("[3,3,null,4,2]").get()));
    ASSERT_EQ(1, solution.goodNodes(Codec::createTree("[1]").get()));
}

}