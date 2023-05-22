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
    [[nodiscard]] TreeNode* replaceValueInTree(TreeNode* root) const
    {
        std::vector<int> levelSums;
        generateLevelSums(root, 0, levelSums);
        return generateCousinsValuesTree(root, nullptr, 0, levelSums);
    }

private:
    void generateLevelSums(TreeNode* root, size_t level, std::vector<int> &levelSums) const
    {
        if (level == levelSums.size())
            levelSums.emplace_back(0);
        levelSums[level] += root->val;
        if (root->left != nullptr)
            generateLevelSums(root->left, level + 1, levelSums);
        if (root->right != nullptr)
            generateLevelSums(root->right, level + 1, levelSums);
    }

    [[nodiscard]] TreeNode* generateCousinsValuesTree(const TreeNode* current, const TreeNode* parent, size_t level, std::vector<int> const &levelSums) const
    {
        if (current == nullptr)
            return nullptr;
        TreeNode* destNode = new TreeNode(parent == nullptr ? 0 : levelSums[level] - calcChildrenSum(parent));
        destNode->left = generateCousinsValuesTree(current->left, current, level + 1, levelSums);
        destNode->right = generateCousinsValuesTree(current->right, current, level + 1, levelSums);
        return destNode;
    }

    [[nodiscard]] int calcChildrenSum(const TreeNode* root) const
    {
        return (root->left == nullptr ? 0 : root->left->val) + (root->right == nullptr ? 0 : root->right->val);
    }
};

}

using CommonLib::createTreeHolder;
using CommonLib::Codec;

namespace CousinsInBinaryTreeIITask
{

TEST(CousinsInBinaryTreeIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("[0,0,0,7,7,null,11]",
              Codec::createData(createTreeHolder(solution.replaceValueInTree(Codec::createTree("[5,4,9,1,10,null,7]").get()))));
    ASSERT_EQ("[0,0,0]",
              Codec::createData(createTreeHolder(solution.replaceValueInTree(Codec::createTree("[3,1,2]").get()))));
}

}