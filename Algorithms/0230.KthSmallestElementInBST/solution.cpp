#include <stack>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int kthSmallest(TreeNode* root, int k) const
    {
        std::stack<TreeNode*> stack;
        stack.push(root);
        bool lastPushed = true;
        int elementNumber = 0;
        while (!stack.empty())
        {
            if (lastPushed && stack.top()->left != nullptr)
            {
                stack.push(stack.top()->left);
                continue;
            }
            TreeNode* current = stack.top();
            stack.pop();
            ++elementNumber;
            if (elementNumber == k)
                return current->val;
            if (current->right != nullptr)
            {
                stack.push(current->right);
                lastPushed = true;
            }
            else
                lastPushed = false;
        }
        return 0;
    }
};

}

using CommonLib::Codec;

namespace KthSmallestElementInBSTTask
{

TEST(KthSmallestElementInBSTTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.kthSmallest(Codec::createTree("[3,1,4,null,2]").get(), 1));
    ASSERT_EQ(3, solution.kthSmallest(Codec::createTree("[5,3,6,2,4,null,null,1]").get(), 3));
}

TEST(KthSmallestElementInBSTTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.kthSmallest(Codec::createTree("[1,null,2]").get(), 2));
}

}