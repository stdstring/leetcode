#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

enum Direction {Left, Right};

class Solution
{
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

using CommonLib::Codec;

namespace SumOfLeftLeavesTask
{

TEST(SumOfLeftLeavesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(24, solution.sumOfLeftLeaves(Codec::createTree("[3,9,20,null,null,15,7]").get()));
}

TEST(SumOfLeftLeavesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.sumOfLeftLeaves(Codec::createTree("[1]").get()));
    ASSERT_EQ(0, solution.sumOfLeftLeaves(Codec::createTree("[]").get()));
    ASSERT_EQ(2, solution.sumOfLeftLeaves(Codec::createTree("[1,2]").get()));
}

}