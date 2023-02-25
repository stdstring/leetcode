#include <queue>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    bool isEvenOddTree(TreeNode* root) const
    {
        std::queue<TreeNode*> nodeQueue;
        std::queue<int> levelQueue;
        int currentLevel = -1;
        int currentValue = 0;
        nodeQueue.push(root);
        levelQueue.push(0);
        while (!nodeQueue.empty())
        {
            if ((nodeQueue.front()->val % 2) != ((levelQueue.front() + 1) % 2))
                return false;
            if (currentLevel == levelQueue.front())
            {
                if ((currentLevel % 2 == 0) && (nodeQueue.front()->val <= currentValue))
                    return false;
                if ((currentLevel % 2 == 1) && (nodeQueue.front()->val >= currentValue))
                    return false;
            }
            currentLevel = levelQueue.front();
            currentValue = nodeQueue.front()->val;
            pushNode(nodeQueue.front()->left, currentLevel, nodeQueue, levelQueue);
            pushNode(nodeQueue.front()->right, currentLevel, nodeQueue, levelQueue);
            nodeQueue.pop();
            levelQueue.pop();
        }
        return true;
    }

private:
    void pushNode(TreeNode* node, int level, std::queue<TreeNode*> &nodeQueue, std::queue<int> &levelQueue) const
    {
        if (node != nullptr)
        {
            nodeQueue.push(node);
            levelQueue.push(level + 1);
        }
    }
};

}

using CommonLib::Codec;

namespace EvenOddTreeTask
{

TEST(LowestCommonAncestorOfBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isEvenOddTree(Codec::createTree("[1,10,4,3,null,7,9,12,8,6,null,null,2]").get()));
    ASSERT_EQ(false, solution.isEvenOddTree(Codec::createTree("[5,4,2,3,3,7]").get()));
    ASSERT_EQ(false, solution.isEvenOddTree(Codec::createTree("[5,9,1,3,5,7]").get()));
    ASSERT_EQ(true, solution.isEvenOddTree(Codec::createTree("[1]").get()));
    ASSERT_EQ(true, solution.isEvenOddTree(Codec::createTree("[11,8,6,1,3,9,11,30,20,18,16,12,10,4,2,17]").get()));
}

}