#include <algorithm>
#include <unordered_set>
#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int maxProduct(TreeNode* root) const
    {
        std::unordered_set<int64_t> subtreeSums;
        const int64_t treeSum = calcSubtreeSum(root, subtreeSums);
        constexpr int modValue = 1000000007;
        int64_t maxProductValue = 0;
        for (int64_t subtreeSum : subtreeSums)
            maxProductValue = std::max(maxProductValue, subtreeSum * (treeSum - subtreeSum));
        return static_cast<int>(maxProductValue % modValue);
    }

private:
    int64_t calcSubtreeSum(TreeNode* root, std::unordered_set<int64_t> &subtreeSums) const
    {
        const int64_t leftSum = root->left == nullptr ? 0 : calcSubtreeSum(root->left, subtreeSums);
        const int64_t rightSum = root->right == nullptr ? 0 : calcSubtreeSum(root->right, subtreeSums);
        const int64_t currentSum = root->val + leftSum + rightSum;
        subtreeSums.insert(currentSum);
        return currentSum;
    }
};

}

using CommonLib::Codec;

namespace MaximumProductOfSplittedBinaryTreeTask
{

TEST(MaximumProductOfSplittedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(110, solution.maxProduct(Codec::createTree("[1,2,3,4,5,6]").get()));
    ASSERT_EQ(90, solution.maxProduct(Codec::createTree("[1,null,2,3,4,null,null,5,6]").get()));
    ASSERT_EQ(1025, solution.maxProduct(Codec::createTree("[2,3,9,10,7,8,6,5,4,11,1]").get()));
    ASSERT_EQ(1, solution.maxProduct(Codec::createTree("[1,1]").get()));
}

}