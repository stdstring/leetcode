#include <memory>
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
    TreeNode* reverseOddLevels(TreeNode* root) const
    {
        std::vector<std::vector<TreeNode*>> oddLevels;
        collectOddLevels(root, 0, oddLevels);
        for (std::vector<TreeNode*> const &oddLevel : oddLevels)
            reverseOddLevel(oddLevel);
        return root;
    }

private:
    void collectOddLevels(TreeNode* root, size_t level, std::vector<std::vector<TreeNode*>> &oddLevels) const
    {
        if ((level % 2) == 1)
        {
            const size_t index = level / 2;
            if (oddLevels.size() == index)
                oddLevels.emplace_back(std::vector<TreeNode*>());
            oddLevels[index].push_back(root);
        }
        if (root->left != nullptr)
            collectOddLevels(root->left, level + 1, oddLevels);
        if (root->right != nullptr)
            collectOddLevels(root->right, level + 1, oddLevels);
    }

    void reverseOddLevel(std::vector<TreeNode*> const &oddLevel) const
    {
        if (oddLevel.size() == 1)
            return;
        for (size_t left = 0, right = oddLevel.size() - 1; left < right; ++left, --right)
            std::swap(oddLevel[left]->val, oddLevel[right]->val);
    }
};

}

using CommonLib::Codec;

namespace
{

void checkReverseOddLevels(std::string const &source, std::string const &expected)
{
    constexpr Solution solution;
    const std::shared_ptr<TreeNode> root(Codec::createTree(source));
    ASSERT_EQ(expected, Codec::createDataRaw(solution.reverseOddLevels(root.get())));
}

}

namespace ReverseOddLevelsOfBinaryTreeTask
{

TEST(ReverseOddLevelsOfBinaryTreeTaskTests, Examples)
{
    checkReverseOddLevels("[2,3,5,8,13,21,34]", "[2,5,3,8,13,21,34]");
    checkReverseOddLevels("[7,13,11]", "[7,11,13]");
    checkReverseOddLevels("[0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]", "[0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]");
}

}