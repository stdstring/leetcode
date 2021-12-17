#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) const
    {
        if (root == nullptr)
            return nullptr;
        TreeNode* left = root->val >= low ? trimBST(root->left, low, high) : nullptr;
        TreeNode* right = root->val <= high ? trimBST(root->right, low, high) : nullptr;
        TreeNode* current = (low <= root->val) && (root->val <= high) ? new TreeNode(root->val) : nullptr;
        if (current != nullptr)
        {
            current->left = left;
            current->right = right;
            return current;
        }
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        TreeNode* leftMostNode = right;
        while (leftMostNode->left != nullptr)
            leftMostNode = leftMostNode->left;
        leftMostNode->left = left;
        return right;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace TrimBinarySearchTreeTask
{

TEST(TrimBinarySearchTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[1,null,2]", Codec::createData(createTreeHolder(solution.trimBST(Codec::createTree("[1,0,2]").get(), 1, 2))));
    ASSERT_EQ("[3,2,null,1]", Codec::createData(createTreeHolder(solution.trimBST(Codec::createTree("[3,0,4,null,2,null,null,1]").get(), 1, 3))));
}

}