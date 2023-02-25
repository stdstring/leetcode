#include <stack>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

enum ProcessState {Children, Self};

class Solution
{
public:
    std::vector<int> postorderTraversal(TreeNode* root) const
    {
        if (root == nullptr)
            return {};
        std::vector<int> dest;
        std::stack<TreeNode*> nodesStack;
        std::stack<ProcessState> processStateStack;
        nodesStack.push(root);
        processStateStack.push(ProcessState::Children);
        while (!nodesStack.empty())
        {
            TreeNode* node = nodesStack.top();
            const ProcessState state = processStateStack.top();
            processStateStack.pop();
            switch (state)
            {
                case ProcessState::Children:
                    if (node->left == nullptr && node->right == nullptr)
                        processSelf(node, dest, nodesStack);
                    else
                    {
                        processStateStack.push(ProcessState::Self);
                        addChild(node->right, nodesStack, processStateStack);
                        addChild(node->left, nodesStack, processStateStack);
                    }
                    break;
                case ProcessState::Self:
                    processSelf(node, dest, nodesStack);
                    break;
            }
        }
        return dest;
    }

private:
    void addChild(TreeNode* child, std::stack<TreeNode*> &nodesStack, std::stack<ProcessState> &processStateStack) const
    {
        if (child != nullptr)
        {
            nodesStack.push(child);
            processStateStack.push(ProcessState::Children);
        }
    }

    void processSelf(TreeNode* node, std::vector<int> &dest, std::stack<TreeNode*> &nodesStack) const
    {
        dest.push_back(node->val);
        nodesStack.pop();
    }
};

}

using CommonLib::Codec;

namespace BinaryTreePostorderTraversalTask
{

TEST(BinaryTreePostorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 1}), solution.postorderTraversal(Codec::createTree("[1,null,2,3]").get()));
    ASSERT_EQ(std::vector<int>(), solution.postorderTraversal(Codec::createTree("[]").get()));
    ASSERT_EQ(std::vector<int>({1}), solution.postorderTraversal(Codec::createTree("[1]").get()));
    ASSERT_EQ(std::vector<int>({2, 1}), solution.postorderTraversal(Codec::createTree("[1,2]").get()));
    ASSERT_EQ(std::vector<int>({2, 1}), solution.postorderTraversal(Codec::createTree("[1,null,2]").get()));
}

TEST(BinaryTreePostorderTraversalTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3}), solution.postorderTraversal(Codec::createTree("[3,1,2]").get()));
}

}
