#include <vector>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<int> inorderTraversal(TreeNode* root) const
    {
        std::vector<int> dest;
        inorderTraversal(root, dest);
        return dest;
    }

private:
    void inorderTraversal(TreeNode* root, std::vector<int> &dest) const
    {
        if (root == nullptr)
            return;
        inorderTraversal(root->left, dest);
        dest.push_back(root->val);
        inorderTraversal(root->right, dest);
    }
};

}

using CommonDefs::createTreeHolder;

namespace BinaryTreeInorderTraversalTask
{

TEST(BinaryTreeInorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 2}), solution.inorderTraversal(createTreeHolder(new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr))).get()));
}

}