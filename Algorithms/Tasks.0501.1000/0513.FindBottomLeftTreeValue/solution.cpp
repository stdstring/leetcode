#include <utility>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int findBottomLeftValue(TreeNode* root) const
    {
        std::pair<size_t, int> bottomLeftValue = std::make_pair(0, root->val);
        traverseTree(root, 0, bottomLeftValue);
        return bottomLeftValue.second;
    }

private:
    void traverseTree(TreeNode* root, size_t level, std::pair<size_t, int> &bottomLeftValue) const
    {
        if (bottomLeftValue.first < level)
        {
            bottomLeftValue.first = level;
            bottomLeftValue.second = root->val;
        }
        if (root->left != nullptr)
            traverseTree(root->left, level + 1, bottomLeftValue);
        if (root->right != nullptr)
            traverseTree(root->right, level + 1, bottomLeftValue);
    }
};

}

using CommonLib::Codec;

namespace FindBottomLeftTreeValueTask
{

TEST(FindLargestValueInEachTreeRowTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findBottomLeftValue(Codec::createTree("[2,1,3]").get()));
    ASSERT_EQ(7, solution.findBottomLeftValue(Codec::createTree("[1,2,3,4,null,5,6,null,null,7]").get()));
}

}