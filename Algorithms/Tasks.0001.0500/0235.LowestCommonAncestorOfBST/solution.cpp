#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) const
    {
        TreeNode* left = p->val < q->val ? p : q;
        TreeNode* right = q->val > p->val ? q : p;
        if (root->val > left->val && root->val < right->val)
            return root;
        if (root->val == left->val || root->val == right->val)
            return root;
        return lowestCommonAncestor(right->val < root->val ? root->left : root->right, left, right);
    }
};

}

using CommonLib::Codec;
using CommonLib::findNodeByValue;

namespace LowestCommonAncestorOfBSTTask
{

TEST(LowestCommonAncestorOfBSTTaskTests, Examples)
{
    const Solution solution;
    const std::shared_ptr<TreeNode> tree1 = Codec::createTree("[6,2,8,0,4,7,9,null,null,3,5]");
    ASSERT_EQ(6, solution.lowestCommonAncestor(tree1.get(), findNodeByValue(tree1.get(), 2), findNodeByValue(tree1.get(), 8))->val);
    ASSERT_EQ(2, solution.lowestCommonAncestor(tree1.get(), findNodeByValue(tree1.get(), 2), findNodeByValue(tree1.get(), 4))->val);
    const std::shared_ptr<TreeNode> tree2 = Codec::createTree("[2,1]");
    ASSERT_EQ(2, solution.lowestCommonAncestor(tree1.get(), findNodeByValue(tree2.get(), 2), findNodeByValue(tree2.get(), 1))->val);
}

}