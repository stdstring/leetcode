#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    void flatten(TreeNode* root)
    {
        flatten(root, nullptr);
    }

private:
    TreeNode* flatten(TreeNode* root, TreeNode* listTail)
    {
        if (root == nullptr)
            return listTail;
        if (listTail != nullptr)
            listTail->right = root;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        root->left = nullptr;
        root->right = nullptr;
        return flatten(right, flatten(left, root));
    }
};

}

using CommonLib::createTreeHolder;
using CommonLib::checkAndDeleteTree;

namespace FlattenBinaryTreeToLinkedListTask
{

TEST(FlattenBinaryTreeToLinkedListTaskTests, Examples)
{
    Solution solution;
    TreeNode* tree = new TreeNode(1, new TreeNode(2, 3, 4), new TreeNode(5, nullptr, 6));
    solution.flatten(tree);
    checkAndDeleteTree(createTreeHolder(new TreeNode(1, nullptr, new TreeNode(2, nullptr, new TreeNode(3, nullptr, new TreeNode(4, nullptr, new TreeNode(5, nullptr, 6)))))).get(), tree);
}

}