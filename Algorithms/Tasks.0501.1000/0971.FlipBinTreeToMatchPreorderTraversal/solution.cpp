#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<int> flipMatchVoyage(TreeNode* root, std::vector<int> const &voyage) const
    {
        std::vector<int> flippedNodes;
        size_t index = 0;
        if (!tryPreorderTraverse(root, voyage, index, flippedNodes))
            return {-1};
        return flippedNodes;
    }

private:
    bool tryPreorderTraverse(TreeNode* root, std::vector<int> const &preorderTraversal, size_t &index, std::vector<int> &flippedNodes) const
    {
        if (root == nullptr)
            return true;
        if (root->val != preorderTraversal[index])
            return false;
        ++index;
        const bool needFlip = (root->left != nullptr) && (root->left->val != preorderTraversal[index]);
        if (needFlip)
        {
            flippedNodes.push_back(root->val);
            if (!tryPreorderTraverse(root->right, preorderTraversal, index, flippedNodes))
                return false;
            if (!tryPreorderTraverse(root->left, preorderTraversal, index, flippedNodes))
                return false;
        }
        else
        {
            if (!tryPreorderTraverse(root->left, preorderTraversal, index, flippedNodes))
                return false;
            if (!tryPreorderTraverse(root->right, preorderTraversal, index, flippedNodes))
                return false;
        }
        return true;
    }
};

}

using CommonLib::Codec;

namespace FlipBinTreeToMatchPreorderTraversalTask
{

TEST(MinimumDepthOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({-1}), solution.flipMatchVoyage(Codec::createTree("[1,2]").get(), {2, 1}));
    ASSERT_EQ(std::vector<int>({1}), solution.flipMatchVoyage(Codec::createTree("[1,2,3]").get(), {1, 3, 2}));
    ASSERT_EQ(std::vector<int>(), solution.flipMatchVoyage(Codec::createTree("[1,2,3]").get(), {1, 2, 3}));
}

}