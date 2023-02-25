#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool validateBinaryTreeNodes(int n, std::vector<int> const &leftChild, std::vector<int> const &rightChild) const
    {
        std::vector<int> parents(n, -1);
        size_t rootCount = n;
        for (int node = 0; node < n; ++node)
        {
            if (leftChild[node] != -1)
            {
                if ((parents[leftChild[node]] != -1) || isIndirectParent(leftChild[node], node, parents))
                    return false;
                parents[leftChild[node]] = node;
                --rootCount;
            }
            if (rightChild[node] != -1)
            {
                if ((parents[rightChild[node]] != -1) || isIndirectParent(rightChild[node], node, parents))
                    return false;
                parents[rightChild[node]] = node;
                --rootCount;
            }
        }
        return rootCount == 1;
    }

private:
    [[nodiscard]] bool isIndirectParent(int nodeA, int nodeB, std::vector<int> const &parents) const
    {
        while (nodeB != -1)
        {
            if (nodeA == nodeB)
                return true;
            nodeB = parents[nodeB];
        }
        return false;
    }
};

}

namespace ValidateBinaryTreeNodesTask
{

TEST(ValidateBinaryTreeNodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.validateBinaryTreeNodes(4, {1, -1, 3, -1}, {2, -1, -1, -1}));
    ASSERT_EQ(false, solution.validateBinaryTreeNodes(4, {1, -1, 3, -1}, {2, 3, -1, -1}));
    ASSERT_EQ(false, solution.validateBinaryTreeNodes(2, {1, 0}, {-1, -1}));
}

TEST(ValidateBinaryTreeNodesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.validateBinaryTreeNodes(4, {1, 0, 3, -1}, {-1, -1, -1, -1}));
}

}