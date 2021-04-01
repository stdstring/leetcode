#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* deleteNode(TreeNode* root, int key) const
    {
        if (root == nullptr)
            return nullptr;
        if (root->val == key)
            return deleteNode(root);
        TreeNode* parent = nullptr;
        TreeNode* current = root;
        while ((current != nullptr) && (current->val != key))
        {
            parent = current;
            current = current->val > key ? current->left : current->right;
        }
        if (current != nullptr)
            (parent->left == current ? parent->left : parent->right) = deleteNode(current);
        return root;
    }

private:
    TreeNode* deleteNode(TreeNode* node) const
    {
        TreeNode* subtreeRoot = nullptr;
        if (node->left == nullptr)
            subtreeRoot = node->right;
        else if (node->right == nullptr)
            subtreeRoot = node->left;
        else
        {
            TreeNode* rightSubtreeLeftmostNode = node->right;
            TreeNode* leftSubtreeRightmostNode = node->left;
            while ((leftSubtreeRightmostNode->right != nullptr) && (rightSubtreeLeftmostNode->left != nullptr))
            {
                leftSubtreeRightmostNode = leftSubtreeRightmostNode->right;
                rightSubtreeLeftmostNode = rightSubtreeLeftmostNode->left;
            }
            if (rightSubtreeLeftmostNode->left == nullptr)
            {
                subtreeRoot = node->right;
                rightSubtreeLeftmostNode->left = node->left;
            }
            else
            {
                subtreeRoot = node->left;
                leftSubtreeRightmostNode->right = node->right;
            }
        }
        delete node;
        return subtreeRoot;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace DeleteNodeInBSTTask
{

TEST(DeleteNodeInBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[5,4,6,2,null,null,7]", Codec::createData(createTreeHolder(solution.deleteNode(Codec::createTreeRaw("[5,3,6,2,4,null,7]"), 3))));
    ASSERT_EQ("[5,3,6,2,4,null,7]", Codec::createData(createTreeHolder(solution.deleteNode(Codec::createTreeRaw("[5,3,6,2,4,null,7]"), 0))));
    ASSERT_EQ("[]", Codec::createData(createTreeHolder(solution.deleteNode(Codec::createTreeRaw("[]"), 0))));
}

}