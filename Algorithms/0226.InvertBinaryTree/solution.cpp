#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

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

using CommonDefs::createTreeHolder;
using CommonDefs::checkAndDeleteTree;

namespace InvertBinaryTreeTask
{

TEST(InvertBinaryTreeTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteTree(createTreeHolder(new TreeNode(4, new TreeNode(7, new TreeNode(9), new TreeNode(6)), new TreeNode(2, new TreeNode(3), new TreeNode(1)))).get(),
                       solution.invertTree(new TreeNode(4, new TreeNode(2, new TreeNode(1), new TreeNode(3)), new TreeNode(7, new TreeNode(6), new TreeNode(9)))));
}

}