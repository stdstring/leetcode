#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countFairPairs(std::vector<int> const &nums, int lower, int upper) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        return static_cast<long long>(countLE(numbers, upper) - countLE(numbers, lower - 1));
    }

private:
    [[nodiscard]] size_t countLE(std::vector<int> const &numbers, int upper) const
    {
        size_t pairCount = 0;
        for (size_t left = 0, right = numbers.size() - 1; left < right;)
        {
            int pairSum = numbers[left] + numbers[right];
            if (pairSum > upper)
                --right;
            else
            {
                pairCount += (right - left);
                ++left;
            }
        }
        return pairCount;
    }
};

}

namespace CountNumberOfFairPairsTask
{

TEST(CountNumberOfFairPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.countFairPairs({0, 1, 7, 4, 4, 5}, 3, 6));
    ASSERT_EQ(1, solution.countFairPairs({1, 7, 9, 2, 5}, 11, 11));
}

TEST(CountNumberOfFairPairsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.countFairPairs({0, 0, 0, 0, 0, 0}, 0, 0));
}

}