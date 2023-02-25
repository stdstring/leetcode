#include <utility>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

enum class Direction {Left, Right};

class Solution
{
public:
    int longestZigZag(TreeNode* root) const
    {
        if ((root->left == nullptr) && (root->right == nullptr))
            return 0;
        size_t longestZigZagPath = 0;
        if (root->left != nullptr)
        {
            const std::pair<size_t, size_t> leftZigZagPath(calcLongestZigZagPath(root->left, Direction::Left));
            longestZigZagPath = std::max(longestZigZagPath, leftZigZagPath.first + 1);
            longestZigZagPath = std::max(longestZigZagPath, leftZigZagPath.second);
        }
        if (root->right != nullptr)
        {
            const std::pair<size_t, size_t> rightZigZagPath(calcLongestZigZagPath(root->right, Direction::Right));
            longestZigZagPath = std::max(longestZigZagPath, rightZigZagPath.first + 1);
            longestZigZagPath = std::max(longestZigZagPath, rightZigZagPath.second);
        }
        return static_cast<int>(longestZigZagPath);
    }

private:
    std::pair<size_t, size_t> calcLongestZigZagPath(TreeNode* root, Direction direction) const
    {
        if (root == nullptr)
            return {0, 0};
        size_t currentZigZagPath = 0;
        size_t longestZigZagPath = 0;
        if (root->left != nullptr)
        {
            const std::pair<size_t, size_t> leftZigZagPath(calcLongestZigZagPath(root->left, Direction::Left));
            longestZigZagPath = std::max(longestZigZagPath, leftZigZagPath.first + 1);
            longestZigZagPath = std::max(longestZigZagPath, leftZigZagPath.second);
            if (direction == Direction::Right)
                currentZigZagPath = leftZigZagPath.first + 1;
        }
        if (root->right != nullptr)
        {
            const std::pair<size_t, size_t> rightZigZagPath(calcLongestZigZagPath(root->right, Direction::Right));
            longestZigZagPath = std::max(longestZigZagPath, rightZigZagPath.first + 1);
            longestZigZagPath = std::max(longestZigZagPath, rightZigZagPath.second);
            if (direction == Direction::Left)
                currentZigZagPath = rightZigZagPath.first + 1;
        }
        return {currentZigZagPath, longestZigZagPath};
    }
};

}

using CommonLib::Codec;

namespace LongestZigZagPathInBinaryTreeTask
{

TEST(MaximumProductOfSplittedBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.longestZigZag(Codec::createTree("[1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]").get()));
    ASSERT_EQ(4, solution.longestZigZag(Codec::createTree("[1,1,1,null,1,null,null,1,1,null,1]").get()));
    ASSERT_EQ(0, solution.longestZigZag(Codec::createTree("[1]").get()));
}

}