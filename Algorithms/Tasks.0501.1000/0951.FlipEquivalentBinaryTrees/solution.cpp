#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) const
    {
        if (root1 == nullptr)
            return root2 == nullptr;
        if (root2 == nullptr)
            return root1 == nullptr;
        if (root1->val != root2->val)
            return false;
        return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right)) || (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));
    }
};

}

using CommonLib::Codec;

namespace FlipEquivalentBinaryTreesTask
{

TEST(FlipEquivalentBinaryTreesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.flipEquiv(Codec::createTree("[1,2,3,4,5,6,null,null,null,7,8]").get(), Codec::createTree("[1,3,2,null,6,4,5,null,null,null,null,8,7]").get()));
    ASSERT_EQ(true, solution.flipEquiv(Codec::createTree("[]").get(), Codec::createTree("[]").get()));
    ASSERT_EQ(false, solution.flipEquiv(Codec::createTree("[]").get(), Codec::createTree("[1]").get()));
}

}