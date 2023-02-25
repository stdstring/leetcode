#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

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

using CommonLib::Codec;

namespace BinaryTreeInorderTraversalTask
{

TEST(BinaryTreeInorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 2}), solution.inorderTraversal(Codec::createTree("[1,null,2,3]").get()));
}

}