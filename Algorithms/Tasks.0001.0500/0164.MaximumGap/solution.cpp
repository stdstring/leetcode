#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumGap(std::vector<int> const &nums) const
    {
        const std::vector<int> sortedNumbers(radixSort(nums));
        int bestGap = 0;
        for (size_t index = 1; index < sortedNumbers.size(); ++index)
            bestGap = std::max(bestGap, sortedNumbers[index] - sortedNumbers[index - 1]);
        return bestGap;
    }

private:
    [[nodiscard]] std::vector<int> radixSort(std::vector<int> const &numbers) const
    {
        std::vector<int> result(numbers);
        bool sorted = false;
        long long factor = 1;
        while (!sorted)
        {
            std::vector<std::vector<int>> baskets(10, std::vector<int>());
            sorted = true;
            for (const int number : result)
            {
                sorted &= (number <= factor);
                const long long digit = (number / factor) % 10;
                baskets[digit].emplace_back(number);
            }
            for (size_t index = 0, basket = 0, basketIndex = 0; index < result.size(); ++index, ++basketIndex)
            {
                if (basketIndex == baskets[basket].size())
                {
                    basketIndex = 0;
                    ++basket;
                    while (baskets[basket].empty())
                        ++basket;
                }
                result[index] = baskets[basket][basketIndex];
            }
            factor *= 10;
        }
        return result;
    }
};

}

namespace MaximumGapTask
{

TEST(MaximumGapTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumGap({3, 6, 9, 1}));
    ASSERT_EQ(0, solution.maximumGap({10}));
}

TEST(MaximumGapTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(9999999, solution.maximumGap({1, 10000000}));
}

}