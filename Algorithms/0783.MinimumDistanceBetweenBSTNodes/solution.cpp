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
    int minDiffInBST(TreeNode* root) const
    {
        int leftmostValue = 0;
        int rightmostValue = 0;
        return calcMinDiff(root, leftmostValue, rightmostValue);
    }

private:
    int calcMinDiff(TreeNode* root, int &leftmostValue, int &rightmostValue) const
    {
        int minimumDiffValue = INT_MAX;
        if (root->left != nullptr)
        {
            int subtreeRightmostValue = INT_MAX;
            minimumDiffValue = std::min({minimumDiffValue, calcMinDiff(root->left, leftmostValue, subtreeRightmostValue), root->val - subtreeRightmostValue});
        }
        else
            leftmostValue = root->val;
        if (root->right != nullptr)
        {
            int subtreeLeftmostValue = INT_MAX;
            minimumDiffValue = std::min({minimumDiffValue, calcMinDiff(root->right, subtreeLeftmostValue, rightmostValue), subtreeLeftmostValue - root->val});
        }
        else
            rightmostValue = root->val;
        return minimumDiffValue;
    }
};

}

using CommonLib::Codec;

namespace MinimumDistanceBetweenBSTNodesTask
{

TEST(MinimumDistanceBetweenBSTNodesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.minDiffInBST(Codec::createTree("[4,2,6,1,3]").get()));
    ASSERT_EQ(1, solution.minDiffInBST(Codec::createTree("[1,0,48,null,null,12,49]").get()));
}

}