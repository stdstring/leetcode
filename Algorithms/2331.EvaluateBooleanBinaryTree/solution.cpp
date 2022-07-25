#include <stdexcept>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool evaluateTree(TreeNode* root) const
    {
        switch(root->val)
        {
            case 0:
                return false;
            case 1:
                return true;
            case 2:
                return evaluateTree(root->left) || evaluateTree(root->right);
            case 3:
                return evaluateTree(root->left) && evaluateTree(root->right);
            default:
                throw std::logic_error("bad node's value");
        }
    }
};

}

using CommonLib::Codec;

namespace EvaluateBooleanBinaryTreeTask
{

TEST(CountGoodNodesInBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.evaluateTree(Codec::createTree("[2,1,3,null,null,0,1]").get()));
    ASSERT_EQ(false, solution.evaluateTree(Codec::createTree("[0]").get()));
}

}