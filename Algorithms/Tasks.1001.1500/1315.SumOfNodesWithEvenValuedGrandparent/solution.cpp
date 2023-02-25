#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int sumEvenGrandparent(TreeNode* root) const
    {
        int sum = 0;
        if (root->val % 2 == 0)
            sum += sumGrandchildrenValues(root);
        if (root->left != nullptr)
            sum += sumEvenGrandparent(root->left);
        if (root->right != nullptr)
            sum += sumEvenGrandparent(root->right);
        return sum;
    }

private:
    int sumGrandchildrenValues(TreeNode* root) const
    {
        int sum = 0;
        if (root->left != nullptr)
        {
            sum += (root->left->left != nullptr ? root->left->left->val : 0);
            sum += (root->left->right != nullptr ? root->left->right->val : 0);
        }
        if (root->right != nullptr)
        {
            sum += (root->right->left != nullptr ? root->right->left->val : 0);
            sum += (root->right->right != nullptr ? root->right->right->val : 0);
        }
        return sum;
    }
};

}

using CommonLib::Codec;

namespace SumOfNodesWithEvenValuedGrandparentTask
{

TEST(SumOfNodesWithEvenValuedGrandparentTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(18, solution.sumEvenGrandparent(Codec::createTree("[6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]").get()));
    ASSERT_EQ(0, solution.sumEvenGrandparent(Codec::createTree("[1]").get()));
}

}