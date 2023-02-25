#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool hasPathSum(TreeNode* root, int sum) const
    {
        if (root == nullptr)
            return false;
        return hasPathSumImpl(root, sum);
    }

private:
    bool hasPathSumImpl(TreeNode* root, int sum) const
    {
        if (root->left == nullptr && root->right == nullptr)
            return sum == root->val;
        if (root->left != nullptr && hasPathSumImpl(root->left, sum - root->val))
            return true;
        return root->right != nullptr && hasPathSumImpl(root->right, sum - root->val);
    }
};

}

using CommonLib::Codec;

namespace PathSumTask
{

TEST(PathSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.hasPathSum(Codec::createTree("[5,4,8,11,null,13,4,7,2,null,null,null,1]").get(), 22));
}

TEST(PathSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.hasPathSum(Codec::createTree("[1,2]").get(), 1));
    ASSERT_EQ(false, solution.hasPathSum(Codec::createTree("[]").get(), 0));
}

}