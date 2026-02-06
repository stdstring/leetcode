#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minRemoval(std::vector<int> const &nums, int k) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        size_t maxSize = 0;
        size_t start = 0;
        for (size_t end = 0; end < numbers.size(); ++end)
        {
            while ((1LL * numbers[end]) > (1LL * k * numbers[start]))
                ++start;
            maxSize = std::max(maxSize, end - start + 1);
        }
        return static_cast<int>(numbers.size() - maxSize);
    }
};

}

namespace MinRemovalsToBalanceArrayTask
{

TEST(MinRemovalsToBalanceArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minRemoval({2, 1, 5}, 2));
    ASSERT_EQ(2, solution.minRemoval({1, 6, 2, 9}, 3));
    ASSERT_EQ(0, solution.minRemoval({4, 6}, 2));
}

TEST(MinRemovalsToBalanceArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minRemoval({1, 34, 23}, 2));
    ASSERT_EQ(3, solution.minRemoval({32, 607, 740, 134, 944, 91, 410, 155, 493, 89, 12}, 10));
}

}