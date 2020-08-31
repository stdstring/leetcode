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

using CommonLib::createTreeHolder;
using CommonLib::checkAndDeleteTree;

namespace InvertBinaryTreeTask
{

TEST(InvertBinaryTreeTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteTree(createTreeHolder(new TreeNode(4, new TreeNode(7, 9, 6), new TreeNode(2, 3, 1))).get(),
                       solution.invertTree(new TreeNode(4, new TreeNode(2, 1, 3), new TreeNode(7, 6, 9))));
}

}