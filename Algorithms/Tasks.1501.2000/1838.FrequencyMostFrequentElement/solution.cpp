#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFrequency(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        int bestFrequency = 0;
        size_t prefixStart = 0;
        long long prefixSum = 0;
        for (size_t index = 0; index < numbers.size();)
        {
            // current portion size
            size_t end = index;
            while ((end < numbers.size()) && (numbers[end] == numbers[index]))
                ++end;
            // calc possible frequencies
            while ((prefixSum + k) < 1LL * static_cast<int>(numbers[index] * (index - prefixStart)))
            {
                prefixSum -= numbers[prefixStart];
                ++prefixStart;
            }
            bestFrequency = std::max(bestFrequency, static_cast<int>(end - prefixStart));
            // update state
            prefixSum += 1LL * numbers[index] * static_cast<long long>(end - index);
            index = end;
        }
        return bestFrequency;
    }
};

}

namespace FrequencyMostFrequentElementTask
{

TEST(FrequencyMostFrequentElementTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxFrequency({1, 2, 4}, 5));
    ASSERT_EQ(2, solution.maxFrequency({1, 4, 8, 13}, 5));
    ASSERT_EQ(1, solution.maxFrequency({3, 9, 6}, 2));
}

}