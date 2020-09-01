#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* invertTree(TreeNode* root)
    {
        if (root == nullptr)
            return root;
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};

}

using CommonLib::Codec;

namespace InvertBinaryTreeTask
{

TEST(InvertBinaryTreeTaskTests, Examples)
{
    Solution solution;
    const std::shared_ptr<TreeNode> tree = Codec::createTree("[4,2,7,1,3,6,9]");
    solution.invertTree(tree.get());
    ASSERT_EQ("[4,7,2,9,6,3,1]", Codec::createData(tree));
}

}