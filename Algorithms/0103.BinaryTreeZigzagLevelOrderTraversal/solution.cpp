#include <algorithm>
#include <vector>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) const
    {
        std::vector<std::vector<int>> dest;
        processTree(root, 0, dest);
        for (size_t index = 1; index < dest.size(); index += 2)
            std::reverse(dest[index].begin(), dest[index].end());
        return dest;
    }

private:
    void processTree(TreeNode* root, size_t level, std::vector<std::vector<int>> &dest) const
    {
        if (root == nullptr)
            return;
        if (level == dest.size())
            dest.emplace_back();
        dest[level].push_back(root->val);
        processTree(root->left, level + 1, dest);
        processTree(root->right, level + 1, dest);
    }
};

}

using CommonDefs::createTreeHolder;

namespace BinaryTreeZigzagLevelOrderTraversalTask
{

TEST(BinaryTreeZigzagLevelOrderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3}, {20, 9}, {15, 7}}), solution.zigzagLevelOrder(createTreeHolder(new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)))).get()));
}

}