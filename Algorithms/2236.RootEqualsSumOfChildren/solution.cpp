#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool checkTree(TreeNode* root) const
    {
        // binary tree consists of exactly 3 nodes: the root, its left child, and its right child.
        return root->val == (root->left->val + root->right->val);
    }
};

}

using CommonLib::Codec;

namespace RootEqualsSumOfChildrenTask
{

TEST(InvertBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkTree(Codec::createTree("[10,4,6]").get()));
    ASSERT_EQ(false, solution.checkTree(Codec::createTree("[5,3,1]").get()));
}

}