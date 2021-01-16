#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int countNodes(TreeNode* root) const
    {
        if (root == nullptr)
            return 0;
        if (root->right == nullptr)
            return root->left == nullptr ? 1 : 2;
        const size_t height = calcTreeHeight(root);
        const size_t nonLastLevelNodesCount = (1ull << height) - 1;
        return static_cast<int>(nonLastLevelNodesCount + calcLastLevelNodes(root, height));
    }

private:
    size_t calcTreeHeight(TreeNode* root) const
    {
        size_t height = 0;
        while (root != nullptr)
        {
            ++height;
            root = root->left;
        }
        return height - 1;
    }

    #pragma warning(disable:28182)
    size_t calcLastLevelNodes(TreeNode* root, size_t height) const
    {
        size_t lastLevelNodesCount = 0;
        size_t rangeSize = 1ull << height;
        size_t rangeRootLevel = 0;
        TreeNode* rangeRoot = root;
        while ((height - rangeRootLevel) > 1)
        {
            TreeNode* node = rangeRoot->left;
            size_t level = rangeRootLevel + 1;
            while ((height - level) > 1)
            {
                node = node->right;
                ++level;
            }
            if (node->right != nullptr)
            {
                lastLevelNodesCount += (rangeSize / 2);
                rangeSize /= 2;
                ++rangeRootLevel;
                rangeRoot = rangeRoot->right;
            }
            else if (node->left != nullptr)
                return lastLevelNodesCount + (rangeSize / 2) - 1;
            else
            {
                rangeSize /= 2;
                ++rangeRootLevel;
                rangeRoot = rangeRoot->left;
            }
        }
        if (rangeRoot->left != nullptr)
            ++lastLevelNodesCount;
        if (rangeRoot->right != nullptr)
            ++lastLevelNodesCount;
        return lastLevelNodesCount;
    }
    #pragma warning(default:28182)
};

}

using CommonLib::Codec;

namespace CountCompleteTreeNodesTask
{

TEST(CountCompleteTreeNodesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.countNodes(Codec::createTree("[1,2,3,4,5,6]").get()));
    ASSERT_EQ(0, solution.countNodes(nullptr));
    ASSERT_EQ(1, solution.countNodes(Codec::createTree("[1]").get()));
}

TEST(CountCompleteTreeNodesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countNodes(Codec::createTree("[1,2,3,4,5]").get()));
    ASSERT_EQ(8, solution.countNodes(Codec::createTree("[1,2,3,4,5,6,7,8]").get()));
}

}