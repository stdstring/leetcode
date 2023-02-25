#include <queue>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct NodeData
{
    NodeData(TreeNode* node, size_t index, size_t depth) : Node(node), Index(index), Depth(depth)
    {
    }

    TreeNode* Node;
    size_t Index;
    size_t Depth;
};

class Solution
{
public:
    int widthOfBinaryTree(TreeNode* root) const
    {
        size_t width = 1;
        size_t startIndex = 0;
        size_t depth = 0;
        std::queue<NodeData> nodesData;
        nodesData.emplace(root, 0, 0);
        while (!nodesData.empty())
        {
            if (nodesData.front().Depth == depth)
            {
                size_t currentWidth = nodesData.front().Index - startIndex + 1;
                width = std::max(width, currentWidth);
            }
            else
            {
                depth = nodesData.front().Depth;
                startIndex = nodesData.front().Index;
            }
            if (nodesData.front().Node->left != nullptr)
                nodesData.emplace(nodesData.front().Node->left, 2 * nodesData.front().Index, nodesData.front().Depth + 1);
            if (nodesData.front().Node->right != nullptr)
                nodesData.emplace(nodesData.front().Node->right, 2 * nodesData.front().Index + 1, nodesData.front().Depth + 1);
            nodesData.pop();
        }
        return static_cast<int>(width);
    }
};

}

using CommonLib::Codec;

namespace MaxWidthOfBinaryTreeTask
{

TEST(MaxWidthOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.widthOfBinaryTree(Codec::createTree("[1,3,2,5,3,null,9]").get()));
    ASSERT_EQ(2, solution.widthOfBinaryTree(Codec::createTree("[1,3,null,5,3]").get()));
    ASSERT_EQ(2, solution.widthOfBinaryTree(Codec::createTree("[1,3,2,5]").get()));
    ASSERT_EQ(8, solution.widthOfBinaryTree(Codec::createTree("[1,3,2,5,null,null,9,6,null,null,7]").get()));
}


}