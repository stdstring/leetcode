#include <unordered_map>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct NodeData
{
    NodeData(TreeNode* parent, TreeNode* current, size_t currentSize) : Parent(parent), Current(current), CurrentSize(currentSize)
    {
    }

    TreeNode* Parent;
    TreeNode* Current;
    size_t CurrentSize;
};

class Solution
{
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) const
    {
        std::unordered_map<int, NodeData> nodesData;
        calcNodesData(root, nullptr, nodesData);
        const NodeData firstNode = nodesData.at(x);
        const size_t leftSubtreeSize = firstNode.Current->left == nullptr ? 0 : nodesData.at(firstNode.Current->left->val).CurrentSize;
        if (leftSubtreeSize > (n - leftSubtreeSize))
            return true;
        const size_t rightSubtreeSize = firstNode.Current->right == nullptr ? 0 : nodesData.at(firstNode.Current->right->val).CurrentSize;
        if (rightSubtreeSize > (n - rightSubtreeSize))
            return true;
        const size_t parentSize = n - firstNode.CurrentSize;
        if (parentSize > (n - parentSize))
            return true;
        return false;
    }

private:
    size_t calcNodesData(TreeNode* current, TreeNode* parent, std::unordered_map<int, NodeData> &nodesData) const
    {
        if (current == nullptr)
            return 0;
        const size_t leftSubtreeSize = calcNodesData(current->left, current, nodesData);
        const size_t rightSubtreeSize = calcNodesData(current->right, current, nodesData);
        const size_t totalSize = leftSubtreeSize + rightSubtreeSize + 1;
        nodesData.emplace(current->val, NodeData(parent, current, totalSize));
        return totalSize;
    }
};

}

using CommonLib::Codec;

namespace BinaryTreeColoringGameTask
{

TEST(BinaryTreeColoringGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.btreeGameWinningMove(Codec::createTree("[1,2,3,4,5,6,7,8,9,10,11]").get(), 11, 3));
    ASSERT_EQ(false, solution.btreeGameWinningMove(Codec::createTree("[1,2,3]").get(), 3, 1));
}

}