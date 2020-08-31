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

using CommonLib::createTreeHolder;

namespace PathSumTask
{

TEST(PathSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.hasPathSum(createTreeHolder(new TreeNode(5, new TreeNode(4, new TreeNode(11, 7, 2), nullptr), new TreeNode(8, 13, new TreeNode(4, nullptr, 1)))).get(), 22));
}

TEST(PathSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.hasPathSum(createTreeHolder(new TreeNode(1, 2, nullptr)).get(), 1));
    ASSERT_EQ(false, solution.hasPathSum(nullptr, 0));
}

}