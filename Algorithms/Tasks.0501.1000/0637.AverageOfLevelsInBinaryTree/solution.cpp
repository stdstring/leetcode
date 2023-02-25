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
    std::vector<double> averageOfLevels(TreeNode* root) const
    {
        std::vector<double> result;
        std::vector<int> levelCount;
        fillData(root, 0, result, levelCount);
        for (size_t index = 0; index < result.size(); ++index)
            result[index] /= levelCount[index];
        return result;
    }

private:
    void fillData(TreeNode* root, size_t level, std::vector<double> &result, std::vector<int> &levelCount) const
    {
        if (root == nullptr)
            return;
        if (level == result.size())
        {
            result.push_back(root->val);
            levelCount.push_back(1);
        }
        else
        {
            result[level] += root->val;
            ++levelCount[level];
        }
        fillData(root->left, level + 1, result, levelCount);
        fillData(root->right, level + 1, result, levelCount);
    }
};

}

using CommonLib::Codec;

namespace
{

void checkAverageOfLevels(std::string const &tree, std::vector<double> const &expected)
{
    const Solution solution;
    std::vector<double> actual(solution.averageOfLevels(Codec::createTree(tree).get()));
    ASSERT_EQ(expected.size(), actual.size());
    for (size_t index = 0; index < expected.size(); ++index)
        ASSERT_DOUBLE_EQ(expected[index], actual[index]);
}

}

namespace AverageOfLevelsInBinaryTreeTask
{

TEST(AverageOfLevelsInBinaryTreeTaskTests, Examples)
{
    checkAverageOfLevels("[3,9,20,null,15,7]", {3.00000, 14.50000, 11.00000});
    checkAverageOfLevels("[3,9,20,15,7]", {3.00000, 14.50000, 11.00000});
}

}