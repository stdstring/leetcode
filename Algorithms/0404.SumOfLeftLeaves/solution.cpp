#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

enum Direction {Left, Right};

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        return sumOfLeftLeaves(root->left, Direction::Left) + sumOfLeftLeaves(root->right, Direction::Right);
    }

private:
    int sumOfLeftLeaves(TreeNode* root, Direction direction) const
    {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return direction == Direction::Left ? root->val : 0;
        return sumOfLeftLeaves(root->left, Direction::Left) + sumOfLeftLeaves(root->right, Direction::Right);
    }
};

}

using CommonDefs::createTreeHolder;

namespace SumOfLeftLeavesTask
{

TEST(SumOfLeftLeavesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(24, solution.sumOfLeftLeaves(createTreeHolder(new TreeNode(3, 9, new TreeNode(20, 15, 7))).get()));
}

TEST(SumOfLeftLeavesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.sumOfLeftLeaves(createTreeHolder(new TreeNode(1)).get()));
    ASSERT_EQ(0, solution.sumOfLeftLeaves(nullptr));
    ASSERT_EQ(2, solution.sumOfLeftLeaves(createTreeHolder(new TreeNode(1, 2, nullptr)).get()));
}

}