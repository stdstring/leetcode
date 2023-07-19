#include <stack>
#include <string>
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

    [[nodiscard]] TreeNode* constructFromPrePost(std::vector<int> const &preorder, std::vector<int> const &postorder) const
    {
        TreeNode* root = nullptr;
        std::stack<TreeNode*> nodeStack;
        for (size_t preorderIndex = 0, postorderIndex = 0; (preorderIndex < preorder.size()) && (postorderIndex < postorder.size()); ++preorderIndex)
        {
            while (!nodeStack.empty() && (nodeStack.top()->val == postorder[postorderIndex]))
            {
                nodeStack.pop();
                ++postorderIndex;
            }
            TreeNode* current = new TreeNode(preorder[preorderIndex]);
            if (root == nullptr)
                root = current;
            else
                (nodeStack.top()->left == nullptr ? nodeStack.top()->left : nodeStack.top()->right) = current;
            nodeStack.push(current);
        }
        return root;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace
{

void checkConstructFromPrePost(std::string const &expected, std::vector<int> const &preorder, std::vector<int> const &postorder)
{
    constexpr Solution solution;
    ASSERT_EQ(expected, Codec::createData(createTreeHolder(solution.constructFromPrePost(preorder, postorder))));
}

}

namespace ConstructBinTreeFromPreorderPostorderTask
{

TEST(ConstructBinTreeFromPreorderPostorderTaskTests, Examples)
{
    checkConstructFromPrePost("[1,2,3,4,5,6,7]", {1, 2, 4, 5, 3, 6, 7}, {4, 5, 2, 6, 7, 3, 1});
    checkConstructFromPrePost("[1]", {1}, {1});
}

}