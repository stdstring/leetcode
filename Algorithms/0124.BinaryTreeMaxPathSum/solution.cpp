#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int maxPathSum(TreeNode* root) const
    {
        return maxPathSumImpl(root).MaxPath;
    }

private:
    struct PathData
    {
        PathData(int maxPath, int maxBranch) : MaxPath(maxPath), MaxBranch(maxBranch)
        {
        }

        int MaxPath;
        int MaxBranch;
    };

    PathData maxPathSumImpl(TreeNode* root) const
    {
        if (root == nullptr)
            return PathData(INT_MIN, 0);
        const PathData leftData(maxPathSumImpl(root->left));
        const PathData rightData(maxPathSumImpl(root->right));
        const int bestBranch = std::max(root->val, std::max(root->val + leftData.MaxBranch, root->val + rightData.MaxBranch));
        const int bestSum = std::max(bestBranch, std::max(root->val + leftData.MaxBranch + rightData.MaxBranch, std::max(leftData.MaxPath, rightData.MaxPath)));
        return PathData(bestSum, bestBranch);
    }
};

}

using CommonLib::Codec;

namespace BinaryTreeMaxPathSumTask
{

TEST(BinaryTreeMaxPathSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxPathSum(Codec::createTreeRaw("[1,2,3]")));
    ASSERT_EQ(42, solution.maxPathSum(Codec::createTreeRaw("[-10,9,20,null,null,15,7]")));
}

TEST(BinaryTreeMaxPathSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(48, solution.maxPathSum(Codec::createTreeRaw("[5,4,8,11,null,13,4,7,2,null,null,null,1]")));
    ASSERT_EQ(-3, solution.maxPathSum(Codec::createTreeRaw("[-3]")));
}

}