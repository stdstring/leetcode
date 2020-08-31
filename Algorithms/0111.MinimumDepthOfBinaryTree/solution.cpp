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
    int minDepth(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right != nullptr)
            return minDepth(root->right) + 1;
        if (root->left != nullptr && root->right == nullptr)
            return minDepth(root->left) + 1;
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

}

using CommonLib::createTreeHolder;

namespace MinimumDepthOfBinaryTreeTask
{

TEST(MinimumDepthOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minDepth(createTreeHolder(new TreeNode(3, 9, new TreeNode(20, 15, 7))).get()));
}

TEST(MinimumDepthOfBinaryTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minDepth(createTreeHolder(new TreeNode(1, 2, nullptr)).get()));
}

}