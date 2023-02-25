#include <memory>
#include <queue>
#include <string>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) const
    {
        std::queue<TreeNode*> nodes;
        nodes.push(cloned);
        while (!nodes.empty())
        {
            if (nodes.front()->val == target->val)
                return nodes.front();
            if (nodes.front()->left != nullptr)
                nodes.push(nodes.front()->left);
            if (nodes.front()->right != nullptr)
                nodes.push(nodes.front()->right);
            nodes.pop();
        }
        return nullptr;
    }
};

}

using CommonLib::Codec;
using CommonLib::findNodeByValue;

namespace
{

void checkGetTargetCopy(std::string const &data, int target)
{
    const std::shared_ptr<TreeNode> original(Codec::createTree(data));
    const std::shared_ptr<TreeNode> cloned(Codec::createTree(data));
    TreeNode* targetNode = findNodeByValue(original.get(), target);
    const Solution solution;
    TreeNode* clonedNode = solution.getTargetCopy(original.get(), cloned.get(), targetNode);
    ASSERT_NE(nullptr, clonedNode);
    ASSERT_NE(targetNode, clonedNode);
    ASSERT_EQ(targetNode->val, clonedNode->val);
}

}

namespace FindCorrespondingNodeOfBinTreeInCloneTask
{

TEST(FindCorrespondingNodeOfBinTreeInCloneTaskTests, Examples)
{
    checkGetTargetCopy("[7,4,3,null,null,6,19]", 3);
    checkGetTargetCopy("[7]", 7);
    checkGetTargetCopy("[8,null,6,null,5,null,4,null,3,null,2,null,1]", 4);
}

}
