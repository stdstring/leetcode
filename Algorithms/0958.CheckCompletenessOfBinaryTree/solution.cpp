#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isCompleteTree(TreeNode* root) const
    {
        const size_t leftmostLevel = calcLeftmostLevel(root);
        bool allowLastLevelNodes = true;
        return checkTree(root, 1, leftmostLevel, allowLastLevelNodes);
    }

private:
    size_t calcLeftmostLevel(TreeNode* root) const
    {
        return 1 + (root->left == nullptr ? 0 : calcLeftmostLevel(root->left));
    }

    bool checkTree(TreeNode* root, size_t level, size_t leftmostLevel, bool &allowLastLevelNodes) const
    {
        const bool hasLeft = root->left != nullptr;
        const bool hasRight = root->right != nullptr;
        if (level == leftmostLevel)
            return !hasLeft && !hasRight;
        if (level == leftmostLevel - 1)
        {
            if (!allowLastLevelNodes)
                return !hasLeft && !hasRight;
            if (!hasLeft && hasRight)
                return false;
            allowLastLevelNodes = hasRight;
            return (!hasLeft || checkTree(root->left, level + 1, leftmostLevel, allowLastLevelNodes)) && (!hasRight || checkTree(root->right, level + 1, leftmostLevel, allowLastLevelNodes));
        }
        if (!hasLeft || !hasRight)
            return false;
        return checkTree(root->left, level + 1, leftmostLevel, allowLastLevelNodes) && checkTree(root->right, level + 1, leftmostLevel, allowLastLevelNodes);
    }
};

}

using CommonLib::Codec;

namespace CheckCompletenessOfBinaryTreeTask
{

TEST(CheckCompletenessOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isCompleteTree(Codec::createTree("[1,2,3,4,5,6]").get()));
    ASSERT_EQ(false, solution.isCompleteTree(Codec::createTree("[1,2,3,4,5,null,7]").get()));
}

TEST(CheckCompletenessOfBinaryTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isCompleteTree(Codec::createTree("[1,2,3,4,5,6,7,8,9,10,11,12,13,null,null,15]").get()));
}

}