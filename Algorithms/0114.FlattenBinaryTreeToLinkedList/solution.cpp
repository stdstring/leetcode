#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

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

using CommonDefs::createTreeHolder;
using CommonDefs::checkAndDeleteTree;

namespace FlattenBinaryTreeToLinkedListTask
{

TEST(FlattenBinaryTreeToLinkedListTaskTests, Examples)
{
    Solution solution;
    TreeNode* tree = new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(5, nullptr, new TreeNode(6)));
    solution.flatten(tree);
    checkAndDeleteTree(createTreeHolder(new TreeNode(1, nullptr, new TreeNode(2, nullptr, new TreeNode(3, nullptr, new TreeNode(4, nullptr, new TreeNode(5, nullptr, new TreeNode(6))))))).get(), tree);
}

}