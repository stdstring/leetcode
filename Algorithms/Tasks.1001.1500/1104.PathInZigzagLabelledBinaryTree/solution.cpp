#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> pathInZigZagTree(int label) const
    {
        // find level number
        int start = 1;
        int size = 1;
        size_t levelNumber = 1;
        while (label > start + size - 1)
        {
            start += size;
            size *= 2;
            ++levelNumber;
        }
        // find label in left to right labeled tree
        int current = levelNumber % 2 == 1 ? label : start + (start + size - 1 - label);
        // find path
        std::vector<int> path(levelNumber, 0);
        while (levelNumber > 0)
        {
            path[levelNumber - 1] = levelNumber % 2 == 1 ? current : start + size - 1 - (current - start);
            current = current / 2;
            size /= 2;
            start -= size;
            --levelNumber;
        }
        return path;
    }
};

}

namespace PathInZigzagLabelledBinaryTreeTask
{

TEST(PathInZigzagLabelledBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 4, 14}), solution.pathInZigZagTree(14));
    ASSERT_EQ(std::vector<int>({1, 2, 6, 10, 26}), solution.pathInZigZagTree(26));
}

TEST(PathInZigzagLabelledBinaryTreeTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 4, 15, 16}), solution.pathInZigZagTree(16));
}

}