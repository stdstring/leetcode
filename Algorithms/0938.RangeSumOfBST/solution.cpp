#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int rangeSumBST(TreeNode* root, int low, int high) const
    {
        int sum = 0;
        if (low <= root->val && root->val <= high)
            sum += root->val;
        if (root->left != nullptr && low <= root->val)
            sum += rangeSumBST(root->left, low, high);
        if (root->right != nullptr && root->val <= high)
            sum += rangeSumBST(root->right, low, high);
        return sum;
    }
};

}

using CommonLib::Codec;

namespace RangeSumOfBSTTask
{

TEST(RangeSumOfBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(32, solution.rangeSumBST(Codec::createTree("[10,5,15,3,7,null,18]").get(), 7, 15));
    ASSERT_EQ(23, solution.rangeSumBST(Codec::createTree("[10,5,15,3,7,13,18,1,null,6]").get(), 6, 10));
}

}