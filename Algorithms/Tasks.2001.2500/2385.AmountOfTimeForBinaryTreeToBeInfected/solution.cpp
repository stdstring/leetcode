#include <queue>
#include <unordered_map>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct NodeData
{
    NodeData(TreeNode* node, TreeNode* parent) : Node(node), Parent(parent), Infected(false)
    {
    }

    TreeNode* Node;
    TreeNode* Parent;
    bool Infected;
};

class Solution
{
public:
    int amountOfTime(TreeNode* root, int start) const
    {
        std::unordered_map<int, NodeData> nodesData;
        CollectNodesData(root, nullptr, nodesData);
        NodeData &startData = nodesData.at(start);
        startData.Infected = true;
        size_t time = 0;
        std::queue<std::pair<NodeData, size_t>> nodes;
        nodes.emplace(startData, 0);
        while (!nodes.empty())
        {
            const NodeData currentData = nodes.front().first;
            size_t currentTime = nodes.front().second;
            nodes.pop();
            time = std::max(time, currentTime);
            if ((currentData.Node->left != nullptr) && (!nodesData.at(currentData.Node->left->val).Infected))
            {
                NodeData &leftData = nodesData.at(currentData.Node->left->val);
                leftData.Infected = true;
                nodes.emplace(leftData, currentTime + 1);
            }
            if ((currentData.Node->right != nullptr) && (!nodesData.at(currentData.Node->right->val).Infected))
            {
                NodeData &rightData = nodesData.at(currentData.Node->right->val);
                rightData.Infected = true;
                nodes.emplace(rightData, currentTime + 1);
            }
            if ((currentData.Parent != nullptr) && (!nodesData.at(currentData.Parent->val).Infected))
            {
                NodeData &parentData = nodesData.at(currentData.Parent->val);
                parentData.Infected = true;
                nodes.emplace(parentData, currentTime + 1);
            }
        }
        return static_cast<int>(time);
    }

private:
    void CollectNodesData(TreeNode* root, TreeNode* parent, std::unordered_map<int, NodeData> &nodesData) const
    {
        nodesData.emplace(root->val, NodeData(root, parent));
        if (root->left != nullptr)
            CollectNodesData(root->left, root, nodesData);
        if (root->right != nullptr)
            CollectNodesData(root->right, root, nodesData);
    }
};

}

using CommonLib::Codec;

namespace AmountOfTimeForBinaryTreeToBeInfectedTask
{

TEST(AmountOfTimeForBinaryTreeToBeInfectedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.amountOfTime(Codec::createTree("[1,5,3,null,4,10,6,9,2]").get(), 3));
    ASSERT_EQ(0, solution.amountOfTime(Codec::createTree("[1]").get(), 1));
}

TEST(AmountOfTimeForBinaryTreeToBeInfectedTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.amountOfTime(Codec::createTree("[2,5]").get(), 5));
}

}