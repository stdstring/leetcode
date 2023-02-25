#include <stack>
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
    std::vector<int> preorderTraversal(TreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<int> dest;
        std::stack<TreeNode*> traversalStack;
        traversalStack.push(root);
        while (!traversalStack.empty())
        {
            TreeNode* current = traversalStack.top();
            traversalStack.pop();
            dest.push_back(current->val);
            if (current->right != nullptr)
                traversalStack.push(current->right);
            if (current->left != nullptr)
                traversalStack.push(current->left);
        }
        return dest;
    }
};

}

using CommonLib::Codec;

namespace BinaryTreePreorderTraversalTask
{

TEST(BinaryTreePreorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3}), solution.preorderTraversal(Codec::createTree("[1,null,2,3]").get()));
}

}