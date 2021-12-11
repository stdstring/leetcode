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
    int deepestLeavesSum(TreeNode* root) const
    {
        size_t currentLevel = 0;
        int leavesSum = 0;
        std::queue<std::pair<TreeNode*, size_t>> nodes;
        nodes.emplace(root, 0);
        while (!nodes.empty())
        {
            std::pair<TreeNode*, size_t> const &data(nodes.front());
            if (currentLevel != data.second)
            {
                currentLevel = data.second;
                leavesSum = 0;
            }
            if (data.first->left == nullptr && data.first->right == nullptr)
                leavesSum += data.first->val;
            if (data.first->left != nullptr)
                nodes.emplace(data.first->left, data.second + 1);
            if (data.first->right != nullptr)
                nodes.emplace(data.first->right, data.second + 1);
            nodes.pop();
        }
        return leavesSum;
    }
};

}

using CommonLib::Codec;

namespace DeepestLeavesSumTask
{

TEST(DeepestLeavesSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(15, solution.deepestLeavesSum(Codec::createTree("[1,2,3,4,5,null,6,7,null,null,null,null,8]").get()));
    ASSERT_EQ(19, solution.deepestLeavesSum(Codec::createTree("[6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]").get()));
}

}