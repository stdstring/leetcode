#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isValidBST(TreeNode* root) const
    {
        if (root == nullptr)
            return true;
        int minValue = 0;
        int maxValue = 0;
        return isValidBST(root, minValue, maxValue);
    }

private:
    bool isValidBST(TreeNode* root, int &minValue, int &maxValue) const
    {
        minValue = root->val;
        maxValue = root->val;
        if (root->left != nullptr)
        {
            int leftMinValue = 0;
            int leftMaxValue = 0;
            if (!isValidBST(root->left, leftMinValue, leftMaxValue))
                return false;
            if (leftMaxValue >= root->val)
                return false;
            minValue = leftMinValue;
        }
        if (root->right != nullptr)
        {
            int rightMinValue = 0;
            int rightMaxValue = 0;
            if (!isValidBST(root->right, rightMinValue, rightMaxValue))
                return false;
            if (rightMinValue <= root->val)
                return false;
            maxValue = rightMaxValue;
        }
        return true;
    }
};

}

using CommonLib::Codec;

namespace ValidateBinarySearchTreeTask
{

TEST(ValidateBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValidBST(Codec::createTree("[2,1,3]").get()));
    ASSERT_EQ(false, solution.isValidBST(Codec::createTree("[5,1,4,null,null,3,6]").get()));
}

TEST(ValidateBinarySearchTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isValidBST(Codec::createTree("[]").get()));
    ASSERT_EQ(false, solution.isValidBST(Codec::createTree("[10,5,15,null,null,6,20]").get()));
}

}