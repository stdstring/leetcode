#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isUnivalTree(TreeNode* root) const
    {
        return isUnivalTreeImpl(root, root->val);
    }

private:
    bool isUnivalTreeImpl(TreeNode* root, int value) const
    {
        if (root == nullptr)
            return true;
        if (root->val != value)
            return false;
        return isUnivalTreeImpl(root->left, value) && isUnivalTreeImpl(root->right, value);
    }
};

}

using CommonLib::Codec;

namespace UnivaluedBinaryTreeTask
{

TEST(UnivaluedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isUnivalTree(Codec::createTree("[1,1,1,1,1,null,1]").get()));
    ASSERT_EQ(false, solution.isUnivalTree(Codec::createTree("[2,2,2,5,2]").get()));
}

}