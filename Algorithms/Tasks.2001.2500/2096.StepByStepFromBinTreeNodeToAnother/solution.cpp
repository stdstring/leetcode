#include <queue>
#include <string>
#include <unordered_map>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string getDirections(TreeNode* root, int startValue, int destValue) const
    {
        std::unordered_map<int, NodeData> nodesMap;
        std::queue<NodeData> nodes;
        nodes.emplace(root, nullptr, 0);
        while (!nodes.empty())
        {
            nodesMap.emplace(nodes.front().Current->val, nodes.front());
            if (nodes.front().Current->left != nullptr)
                nodes.emplace(nodes.front().Current->left, nodes.front().Current, nodes.front().Level + 1);
            if (nodes.front().Current->right != nullptr)
                nodes.emplace(nodes.front().Current->right, nodes.front().Current, nodes.front().Level + 1);
            nodes.pop();
        }
        std::string path;
        std::string downPath;
        NodeData startNode = nodesMap.at(startValue);
        NodeData destNode = nodesMap.at(destValue);
        while (startNode.Level > destNode.Level)
        {
            path.push_back('U');
            startNode = nodesMap.at(startNode.Parent->val);
        }
        while (startNode.Level < destNode.Level)
        {
            downPath.push_back(destNode.Parent->left == destNode.Current ? 'L' : 'R');
            destNode = nodesMap.at(destNode.Parent->val);
        }
        while (startNode.Current != destNode.Current)
        {
            path.push_back('U');
            startNode = nodesMap.at(startNode.Parent->val);
            downPath.push_back(destNode.Parent->left == destNode.Current ? 'L' : 'R');
            destNode = nodesMap.at(destNode.Parent->val);
        }
        return path.append(downPath.crbegin(), downPath.crend());
    }

private:
    struct NodeData
    {
        NodeData(TreeNode* current, TreeNode* parent, size_t level) : Current(current), Parent(parent), Level(level)
        {
        }

        TreeNode* Current;
        TreeNode* Parent;
        size_t Level;
    };
};

}

using CommonLib::Codec;

namespace StepByStepFromBinTreeNodeToAnotherTask
{

TEST(StepByStepFromBinTreeNodeToAnotherTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("UURL", solution.getDirections(Codec::createTree("[5,1,2,3,null,6,4]").get(), 3, 6));
    ASSERT_EQ("L", solution.getDirections(Codec::createTree("[2,1]").get(), 2, 1));
}

}