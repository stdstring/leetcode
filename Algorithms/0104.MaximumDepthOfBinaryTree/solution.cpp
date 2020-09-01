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
    int maxDepth(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

}

using CommonLib::Codec;

namespace MaximumDepthOfBinaryTreeTask
{

TEST(MaximumDepthOfBinaryTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.maxDepth(Codec::createTree("[3,9,20,null,null,15,7]").get()));
}

}