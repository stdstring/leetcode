#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMinFibonacciNumbers(int k) const
    {
        std::vector<int> fibonacciNumbers({1, 1});
        while ((fibonacciNumbers[fibonacciNumbers.size() - 1] + fibonacciNumbers[fibonacciNumbers.size() - 2]) <= k)
            fibonacciNumbers.emplace_back(fibonacciNumbers[fibonacciNumbers.size() - 1] + fibonacciNumbers[fibonacciNumbers.size() - 2]);
        size_t usedNumbersCount = 0;
        auto iterator = fibonacciNumbers.crbegin();
        while (k > 0)
        {
            while (*iterator > k)
                ++iterator;
            usedNumbersCount += (k / *iterator);
            k %= *iterator;
        }
        return static_cast<int>(usedNumbersCount);
    }
};

}

namespace FindMinNumOfFibonacciNumsWhoseSumKTask
{

TEST(FindMinNumOfFibonacciNumsWhoseSumKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findMinFibonacciNumbers(7));
    ASSERT_EQ(2, solution.findMinFibonacciNumbers(10));
    ASSERT_EQ(3, solution.findMinFibonacciNumbers(19));
}

}