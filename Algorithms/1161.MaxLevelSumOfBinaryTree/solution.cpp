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
    int maxLevelSum(TreeNode* root) const
    {
        size_t bestLevel = 0;
        int bestSum = INT_MIN;
        std::queue<std::pair<TreeNode*, size_t>> nodes;
        nodes.emplace(root, 1);
        size_t currentLevel = 1;
        int currentSum = 0;
        while (!nodes.empty())
        {
            if (nodes.front().second != currentLevel)
            {
                if (currentSum > bestSum)
                {
                    bestSum = currentSum;
                    bestLevel = currentLevel;
                }
                currentLevel = nodes.front().second;
                currentSum = nodes.front().first->val;
            }
            else
                currentSum += nodes.front().first->val;
            if (nodes.front().first->left != nullptr)
                nodes.emplace(nodes.front().first->left, nodes.front().second + 1);
            if (nodes.front().first->right != nullptr)
                nodes.emplace(nodes.front().first->right, nodes.front().second + 1);
            nodes.pop();
        }
        return static_cast<int>(currentSum > bestSum ? currentLevel : bestLevel);
    }
};

}

using CommonLib::Codec;

namespace MaxLevelSumOfBinaryTreeTask
{

TEST(SmallestSubtreeWithAllDeepestNodesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.maxLevelSum(Codec::createTree("[1,7,0,7,-8,null,null]").get()));
    ASSERT_EQ(2, solution.maxLevelSum(Codec::createTree("[989,null,10250,98693,-89388,null,null,null,-32127]").get()));
}

}
