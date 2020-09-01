#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isSymmetric(TreeNode* root) const
    {
        if (root == nullptr)
            return true;
        return isSymmetric(root->left, root->right);
    }

private:
    bool isSymmetric(TreeNode* left, TreeNode* right) const
    {
        if (left == nullptr)
            return right == nullptr;
        if (right == nullptr)
            return false;
        if (left->val != right->val)
            return false;
        if (!isSymmetric(left->left, right->right))
            return false;
        return isSymmetric(left->right, right->left);
    }
};

}

using CommonLib::Codec;

namespace SymmetricTreeTask
{

TEST(SymmetricTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSymmetric(Codec::createTree("[1,2,2,3,4,4,3]").get()));
    ASSERT_EQ(false, solution.isSymmetric(Codec::createTree("[1,2,2,null,3,null,3]").get()));
}

TEST(SymmetricTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSymmetric(Codec::createTree("[]").get()));
}

}