#include <unordered_map>
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
    [[nodiscard]] TreeNode* createBinaryTree(std::vector<std::vector<int>> const &descriptions) const
    {
        std::unordered_map<int, TreeData> nodeMap;
        for (std::vector<int> const &description : descriptions)
        {
            int parent = description[0];
            int child = description[1];
            const bool isLeft = description[2];
            auto parentEntry = nodeMap.find(parent);
            if (parentEntry == nodeMap.end())
                parentEntry = nodeMap.emplace(parent, TreeData(new TreeNode(parent), false)).first;
            auto childEntry = nodeMap.find(child);
            if (childEntry == nodeMap.end())
                childEntry = nodeMap.emplace(child, TreeData(new TreeNode(child), true)).first;
            (isLeft ? parentEntry->second.Node->left : parentEntry->second.Node->right) = childEntry->second.Node;
            childEntry->second.HasParent = true;
        }
        for (auto const &entry : nodeMap)
        {
            if (!entry.second.HasParent)
                return entry.second.Node;
        }
        return nullptr;
    }

private:
    struct TreeData
    {
        TreeData(TreeNode* node, bool hasParent) : Node(node), HasParent(hasParent)
        {
        }

        TreeNode* Node;
        bool HasParent;
    };
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace CreateBinaryTreeFromDescriptionsTask
{

TEST(CreateBinaryTreeFromDescriptionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("[50,20,80,15,17,19]",
              Codec::createData(createTreeHolder(solution.createBinaryTree({{20, 15, 1}, {20, 17, 0}, {50, 20, 1}, {50, 80, 0}, {80, 19, 1}}))));
    ASSERT_EQ("[1,2,null,null,3,4]",
              Codec::createData(createTreeHolder(solution.createBinaryTree({{1, 2, 1}, {2, 3, 0}, {3, 4, 1}}))));
}

}