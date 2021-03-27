#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numTrees(int n) const
    {
        std::vector<int> treesCount;
        treesCount.push_back(1);
        treesCount.push_back(1);
        for (int number = 2; number <= n; ++number)
        {
            treesCount.push_back(0);
            for (int leftTreeSize = 0; leftTreeSize < number; ++leftTreeSize)
            {
                const int rightTreeSize = number - leftTreeSize - 1;
                treesCount.back() += (treesCount[leftTreeSize] * treesCount[rightTreeSize]);
            }
        }
        return treesCount.back();
    }
};

}

namespace UniqueBinarySearchTreesTask
{

TEST(UniqueBinarySearchTreesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.numTrees(3));
    ASSERT_EQ(1, solution.numTrees(1));
}

}