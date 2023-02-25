#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct PathData
{
    PathData(size_t currentMaxPath, size_t totalMaxPath) : CurrentMaxPath(currentMaxPath), TotalMaxPath(totalMaxPath)
    {
    }

    size_t CurrentMaxPath;
    size_t TotalMaxPath;
};

class Solution
{
public:
    int longestUnivaluePath(TreeNode* root) const
    {
        return root == nullptr ? 0 : static_cast<int>(findLongestUnivaluePath(root).TotalMaxPath);
    }

private:
    PathData findLongestUnivaluePath(TreeNode const* root) const
    {
        PathData pathData(0, 0);
        size_t totalMaxPath = 0;
        if (root->left != nullptr)
        {
            const PathData leftPathData(findLongestUnivaluePath(root->left));
            if (root->val == root->left->val)
            {
                pathData.CurrentMaxPath = std::max(leftPathData.CurrentMaxPath + 1, pathData.CurrentMaxPath);
                totalMaxPath += (1 + leftPathData.CurrentMaxPath);
            }
            pathData.TotalMaxPath = std::max(pathData.TotalMaxPath, leftPathData.TotalMaxPath);
        }
        if (root->right != nullptr)
        {
            const PathData rightPathData(findLongestUnivaluePath(root->right));
            if (root->val == root->right->val)
            {
                pathData.CurrentMaxPath = std::max(rightPathData.CurrentMaxPath + 1, pathData.CurrentMaxPath);
                totalMaxPath += (1 + rightPathData.CurrentMaxPath);
            }
            pathData.TotalMaxPath = std::max(pathData.TotalMaxPath, rightPathData.TotalMaxPath);
        }
        pathData.TotalMaxPath = std::max(pathData.TotalMaxPath, totalMaxPath);
        return pathData;
    }
};

}

using CommonLib::Codec;

namespace LongestUnivaluePathTask
{

TEST(LongestUnivaluePathTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.longestUnivaluePath(Codec::createTree("[5,4,5,1,1,5]").get()));
    ASSERT_EQ(2, solution.longestUnivaluePath(Codec::createTree("[1,4,5,4,4,5]").get()));
}

TEST(LongestUnivaluePathTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.longestUnivaluePath(Codec::createTree("[]").get()));
}

}