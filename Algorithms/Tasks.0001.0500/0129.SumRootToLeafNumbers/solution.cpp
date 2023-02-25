#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int sumNumbers(TreeNode* root) const
    {
        return root == nullptr ? 0 : sumNumbers(root, 0, 0);
    }

private:
    int sumNumbers(TreeNode* root, int number, int sum) const
    {
        number = number * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr)
            return sum + number;
        if (root->left != nullptr)
            sum = sumNumbers(root->left, number, sum);
        if (root->right != nullptr)
            sum = sumNumbers(root->right, number, sum);
        return sum;
    }
};

}

using CommonLib::Codec;

namespace SumRootToLeafNumbersTask
{

TEST(SumRootToLeafNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(25, solution.sumNumbers(Codec::createTree("[1,2,3]").get()));
    ASSERT_EQ(1026, solution.sumNumbers(Codec::createTree("[4,9,0,5,1]").get()));
}

}