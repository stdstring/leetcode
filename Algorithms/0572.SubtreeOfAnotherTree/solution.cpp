#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isSubtree(TreeNode* s, TreeNode* t) const
    {
        return compare(s, t);
    }

private:
    bool compare(TreeNode* s, TreeNode* t) const
    {
        if (compareSubtree(s, t))
            return true;
        if (s->left != nullptr && compare(s->left, t))
            return true;
        if (s->right != nullptr && compare(s->right, t))
            return true;
        return false;
    }

    bool compareSubtree(TreeNode* s, TreeNode* t) const
    {
        if (s == nullptr)
            return t == nullptr;
        if (t == nullptr)
            return false;
        return (s->val == t->val) && compareSubtree(s->left, t->left) && compareSubtree(s->right, t->right);
    }
};

}

using CommonLib::Codec;

namespace SubtreeOfAnotherTreeTask
{

TEST(SubtreeOfAnotherTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isSubtree(Codec::createTree("[3,4,5,1,2]").get(), Codec::createTree("[4,1,2]").get()));
    ASSERT_EQ(false, solution.isSubtree(Codec::createTree("[3,4,5,1,2,null,null,null,null,0]").get(), Codec::createTree("[4,1,2]").get()));
}

TEST(SubtreeOfAnotherTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isSubtree(Codec::createTree("[3,4,5,1,2]").get(), Codec::createTree("[4,1,2,1]").get()));
    ASSERT_EQ(true, solution.isSubtree(Codec::createTree("[1,1]").get(), Codec::createTree("[1]").get()));
}

}