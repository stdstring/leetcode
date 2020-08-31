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

using CommonLib::createTreeHolder;

namespace SameTreeTask
{

TEST(SameTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSameTree(createTreeHolder(new TreeNode(1, 2, 3)).get(), createTreeHolder(new TreeNode(1, 2, 3)).get()));
    ASSERT_EQ(false, solution.isSameTree(createTreeHolder(new TreeNode(1, 2, nullptr)).get(), createTreeHolder(new TreeNode(1, nullptr, 2)).get()));
    ASSERT_EQ(false, solution.isSameTree(createTreeHolder(new TreeNode(1, 2, 1)).get(), createTreeHolder(new TreeNode(1, 1, 2)).get()));
}

}
