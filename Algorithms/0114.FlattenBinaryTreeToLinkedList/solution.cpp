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

using CommonLib::Codec;

namespace FlattenBinaryTreeToLinkedListTask
{

TEST(FlattenBinaryTreeToLinkedListTaskTests, Examples)
{
    Solution solution;
    const std::shared_ptr<TreeNode> tree = Codec::createTree("[1,2,5,3,4,null,6]");
    solution.flatten(tree.get());
    ASSERT_EQ("[1,null,2,null,3,null,4,null,5,null,6]", Codec::createData(tree));
}

}