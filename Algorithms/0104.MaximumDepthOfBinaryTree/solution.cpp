#include <algorithm>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    int maxDepth(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

}

using CommonDefs::createTreeHolder;

namespace MaximumDepthOfBinaryTreeTask
{

TEST(MaximumDepthOfBinaryTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.maxDepth(createTreeHolder(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))).get()));
}

}