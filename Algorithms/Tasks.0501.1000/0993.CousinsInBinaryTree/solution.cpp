#include <queue>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct NodeData
{
    NodeData(TreeNode* current, size_t depth, TreeNode* parent) : Current(current), Depth(depth), Parent(parent)
    {
    }

    TreeNode* Current;
    size_t Depth;
    TreeNode* Parent;
};

class Solution
{
public:
    bool isCousins(TreeNode* root, int x, int y) const
    {
        std::queue<NodeData> nodes;
        nodes.emplace(root, 0, nullptr);
        bool hasXValue = false;
        bool hasYValue = false;
        size_t currentDepth = 0;
        TreeNode* lastParent = nullptr;
        while (!nodes.empty())
        {
            if (currentDepth != nodes.front().Depth)
            {
                hasXValue = false;
                hasYValue = false;
                currentDepth = nodes.front().Depth;
                lastParent = nullptr;
            }
            if (nodes.front().Current->val == x && ProcessValueEquality(nodes.front().Parent, hasXValue, hasYValue, &lastParent))
                return true;
            if (nodes.front().Current->val == y && ProcessValueEquality(nodes.front().Parent, hasYValue, hasXValue, &lastParent))
                return true;
            if (nodes.front().Current->left != nullptr)
                nodes.emplace(nodes.front().Current->left, nodes.front().Depth + 1, nodes.front().Current);
            if (nodes.front().Current->right != nullptr)
                nodes.emplace(nodes.front().Current->right, nodes.front().Depth + 1, nodes.front().Current);
            nodes.pop();
        }
        return false;
    }

private:
    bool ProcessValueEquality(TreeNode* parent, bool &hasValue, bool hasOtherValue, TreeNode** lastParent) const
    {
        if (hasOtherValue && *lastParent != parent)
            return true;
        hasValue = true;
        *lastParent = parent;
        return false;
    }
};

}

using CommonLib::Codec;

namespace CousinsInBinaryTreeTask
{

TEST(SmallestStringStartingFromLeafTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isCousins(Codec::createTree("[1,2,3,4]").get(), 4, 3));
    ASSERT_EQ(true, solution.isCousins(Codec::createTree("[1,2,3,null,4,null,5]").get(), 5, 4));
    ASSERT_EQ(false, solution.isCousins(Codec::createTree("[1,2,3,null,4]").get(), 2, 3));
}

}