#include <algorithm>
#include <iterator>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    long long kthLargestLevelSum(TreeNode* root, int k) const
    {
        std::vector<long long> levelSum;
        calcLevelSum(root, 0, levelSum);
        if (levelSum.size() < static_cast<size_t>(k))
            return -1;
        std::nth_element(levelSum.begin(), std::next(levelSum.begin(), k - 1), levelSum.end(), std::greater<long long>());
        return levelSum[k - 1];
    }

private:
    void calcLevelSum(TreeNode* root, size_t level, std::vector<long long> &levelSum) const
    {
        if (level == levelSum.size())
            levelSum.push_back(0);
        levelSum[level] += root->val;
        if (root->left != nullptr)
            calcLevelSum(root->left, level + 1, levelSum);
        if (root->right != nullptr)
            calcLevelSum(root->right, level + 1, levelSum);
    }
};

}

using CommonLib::Codec;

namespace KthLargestSumInBinaryTreeTask
{

TEST(KthLargestSumInBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.kthLargestLevelSum(Codec::createTree("[5,8,9,2,1,3,7,4,6]").get(), 2));
    ASSERT_EQ(3, solution.kthLargestLevelSum(Codec::createTree("[1,2,null,3]").get(), 1));
}

TEST(KthLargestSumInBinaryTreeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(322918, solution.kthLargestLevelSum(Codec::createTree("[411310,211244,111674]").get(), 2));
}

}