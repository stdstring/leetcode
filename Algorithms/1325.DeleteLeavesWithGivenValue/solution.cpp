#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* removeLeafNodes(TreeNode* root, int target) const
    {
        return processSubtree(root, target);
    }

private:
    TreeNode* processSubtree(TreeNode* root, int target) const
    {
        if (root == nullptr)
            return nullptr;
        TreeNode* left = processSubtree(root->left, target);
        TreeNode* right = processSubtree(root->right, target);
        return (left == nullptr && right == nullptr && root->val == target) ? nullptr : new TreeNode(root->val, left, right);
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace DeleteLeavesWithGivenValueTask
{

TEST(DeleteLeavesWithGivenValueTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[1,null,3,null,4]", Codec::createData(createTreeHolder(solution.removeLeafNodes(Codec::createTree("[1,2,3,2,null,2,4]").get(), 2))));
    ASSERT_EQ("[1,3,null,null,2]", Codec::createData(createTreeHolder(solution.removeLeafNodes(Codec::createTree("[1,3,3,3,2]").get(), 3))));
    ASSERT_EQ("[1]", Codec::createData(createTreeHolder(solution.removeLeafNodes(Codec::createTree("[1,2,null,2,null,2]").get(), 2))));
    ASSERT_EQ("[]", Codec::createData(createTreeHolder(solution.removeLeafNodes(Codec::createTree("[1,1,1]").get(), 1))));
    ASSERT_EQ("[1,2,3]", Codec::createData(createTreeHolder(solution.removeLeafNodes(Codec::createTree("[1,2,3]").get(), 1))));
}

}