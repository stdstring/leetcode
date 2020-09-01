#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isSameTree(TreeNode* p, TreeNode* q) const
    {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr && q != nullptr)
            return false;
        if (p != nullptr && q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        if (!isSameTree(p->left, q->left))
            return false;
        return isSameTree(p->right, q->right);
    }
};

}

using CommonLib::Codec;

namespace SameTreeTask
{

TEST(SameTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSameTree(Codec::createTree("[1,2,3]").get(), Codec::createTree("[1,2,3]").get()));
    ASSERT_EQ(false, solution.isSameTree(Codec::createTree("[1,2]").get(), Codec::createTree("[1,null,2]").get()));
    ASSERT_EQ(false, solution.isSameTree(Codec::createTree("[1,2,1]").get(), Codec::createTree("[1,1,2]").get()));
}

}
