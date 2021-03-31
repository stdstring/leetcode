#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int diameterOfBinaryTree(TreeNode* root) const
    {
        size_t treeDiameter = 0;
        calcHeight(root, treeDiameter);
        return static_cast<int>(treeDiameter);
    }

private:
    size_t calcHeight(TreeNode* root, size_t &treeDiameter) const
    {
        size_t leftDiameter = 0;
        size_t rightDiameter = 0;
        const size_t leftHeight = root->left == nullptr ? 0 : calcHeight(root->left, leftDiameter) + 1;
        const size_t rightHeight = root->right == nullptr ? 0 : calcHeight(root->right, rightDiameter) + 1;
        treeDiameter = std::max({leftDiameter, rightDiameter, leftHeight + rightHeight});
        return std::max(leftHeight, rightHeight);
    }
};

}

using CommonLib::Codec;

namespace DiameterOfBinaryTreeTask
{

TEST(DiameterOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.diameterOfBinaryTree(Codec::createTree("[1,2,3,4,5]").get()));
    ASSERT_EQ(1, solution.diameterOfBinaryTree(Codec::createTree("[1,2]").get()));
}

TEST(DiameterOfBinaryTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(8, solution.diameterOfBinaryTree(Codec::createTree("[4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2]").get()));
}

}