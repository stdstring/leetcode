#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long flowerGame(int n, int m) const
    {
        const long long firstOddCount = (n / 2) + (((n % 2) == 0) ? 0 : 1);
        const long long firstEvenCount = (n / 2);
        const long long secondOddCount = (m / 2) + (((m % 2) == 0) ? 0 : 1);
        const long long secondEvenCount = (m / 2);
        return (firstOddCount * secondEvenCount) + (firstEvenCount * secondOddCount);
    }
};

}

namespace AliceAndBobPlayingFlowerGameTask
{

TEST(AliceAndBobPlayingFlowerGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.flowerGame(3, 2));
    ASSERT_EQ(0, solution.flowerGame(1, 1));
}

TEST(AliceAndBobPlayingFlowerGameTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.flowerGame(5, 4));
}

}