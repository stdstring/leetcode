#include <array>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int pseudoPalindromicPaths(TreeNode* root) const
    {
        std::array<size_t, 10> counts{};
        counts.fill(0);
        return static_cast<int>(countPseudoPalindromicPath(root, counts));
    }

private:
    size_t countPseudoPalindromicPath(TreeNode* root, std::array<size_t, 10> &counts) const
    {
        ++counts[root->val];
        const bool hasLeft = root->left != nullptr;
        const bool hasRight = root->right != nullptr;
        size_t result = 0;
        if (!hasLeft && !hasRight)
            result = isPseudoPalindromicPath(counts) ? 1 : 0;
        else
            result = (hasLeft ? countPseudoPalindromicPath(root->left, counts) : 0) + (hasRight ? countPseudoPalindromicPath(root->right, counts) : 0);
        --counts[root->val];
        return result;
    }

    [[nodiscard]] bool isPseudoPalindromicPath(std::array<size_t, 10> const &counts) const
    {
        size_t oddCount = 0;
        for (const size_t count : counts)
        {
            if (count % 2 == 1)
                ++oddCount;
        }
        return oddCount < 2;
    }
};

}

using CommonLib::Codec;

namespace PseudoPalindromicPathsInBinaryTreeTask
{

TEST(CountGoodNodesInBinaryTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.pseudoPalindromicPaths(Codec::createTree("[2,3,1,3,1,null,1]").get()));
    ASSERT_EQ(1, solution.pseudoPalindromicPaths(Codec::createTree("[2,1,1,1,3,null,null,null,null,null,1]").get()));
    ASSERT_EQ(1, solution.pseudoPalindromicPaths(Codec::createTree("[9]").get()));
}

}