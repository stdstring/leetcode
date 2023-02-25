#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int averageOfSubtree(TreeNode* root) const
    {
        size_t count = 0;
        processTree(root, count);
        return static_cast<int>(count);
    }

private:
    std::pair<int, size_t> processTree(TreeNode* root, size_t &count) const
    {
        if (root == nullptr)
            return {0, 0};
        const std::pair<int, size_t> leftData(processTree(root->left, count));
        const std::pair<int, size_t> rightData(processTree(root->right, count));
        const std::pair<int, size_t> currentData(leftData.first + rightData.first + root->val, leftData.second + rightData.second + 1);
        const int average = currentData.first / static_cast<int>(currentData.second);
        if (average == root->val)
            ++count;
        return currentData;
    }
};

}

using CommonLib::Codec;

namespace CountNodesEqualToSubtreeAverageTask
{

TEST(CountNodesEqualToSubtreeAverageTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.averageOfSubtree(Codec::createTree("[4,8,5,0,1,null,6]").get()));
    ASSERT_EQ(1, solution.averageOfSubtree(Codec::createTree("[1]").get()));
}

}
