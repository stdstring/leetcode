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
    int getMinimumDifference(TreeNode* root) const
    {
        int leftmostValue = 0;
        int rightmostValue = 0;
        return calcMinimumDifference(root, leftmostValue, rightmostValue);
    }

private:
    int calcMinimumDifference(TreeNode* root, int &leftmostValue, int &rightmostValue) const
    {
        int minimumDiffValue = INT_MAX;
        if (root->left != nullptr)
        {
            int subtreeRightmostValue = INT_MAX;
            minimumDiffValue = std::min({minimumDiffValue, calcMinimumDifference(root->left, leftmostValue, subtreeRightmostValue), root->val - subtreeRightmostValue});
        }
        else
            leftmostValue = root->val;
        if (root->right != nullptr)
        {
            int subtreeLeftmostValue = INT_MAX;
            minimumDiffValue = std::min({minimumDiffValue, calcMinimumDifference(root->right, subtreeLeftmostValue, rightmostValue), subtreeLeftmostValue - root->val});
        }
        else
            rightmostValue = root->val;
        return minimumDiffValue;
    }
};

}

using CommonLib::Codec;

namespace MinimumAbsoluteDifferenceInBSTTask
{

TEST(MinimumAbsoluteDifferenceInBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.getMinimumDifference(Codec::createTree("[1,null,3,2]").get()));
}

}