#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int climbStairs(int n) const
    {
        std::vector<long long> storage;
        // first 1 step
        storage.push_back(1);
        // first 2 step
        storage.push_back(1);
        for (int index = 0; index < n; ++index)
        {
            // 1 step
            storage[index + 1] += storage[index];
            // 2 step
            storage.push_back(storage[index]);
        }
        return storage[n - 1];
    }
};

}

namespace ClimbingStairsTask
{

TEST(ClimbingStairsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.climbStairs(2));
    ASSERT_EQ(3, solution.climbStairs(3));
}

TEST(ClimbingStairsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1836311903, solution.climbStairs(45));
}

}