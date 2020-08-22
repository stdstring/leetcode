#include <vector>

#include "TreeNode.h"

#include "gtest/gtest.h"

using CommonDefs::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) const
    {
        std::vector<std::vector<int>> dest;
        levelOrder(root, 0, dest);
        return dest;
    }

private:
    void levelOrder(TreeNode* root, size_t level, std::vector<std::vector<int>> &dest) const
    {
        if (root == nullptr)
            return;
        if (level == dest.size())
            dest.emplace_back();
        dest[level].push_back(root->val);
        levelOrder(root->left, level + 1, dest);
        levelOrder(root->right, level + 1, dest);
    }
};

}

using CommonDefs::createTreeHolder;

namespace BinaryTreeLevelOrderTraversalTask
{

TEST(BinaryTreeLevelOrderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3}, {9, 20}, {15, 7}}), solution.levelOrder(createTreeHolder(new TreeNode(3, 9, new TreeNode(20, 15, 7))).get()));
}

}