#include <algorithm>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums) const
    {
        const std::set<int> numsSet(nums.cbegin(), nums.cend());
        const std::vector<int> numbers(numsSet.cbegin(), numsSet.cend());
        size_t minOpCount = nums.size();
        for (size_t start = 0; start < numbers.size(); ++start)
        {
            const size_t end = findIndex(numbers, static_cast<int>(numbers[start] + nums.size() - 1));
            minOpCount = std::min(minOpCount, nums.size() - (end - start + 1));
        }
        return static_cast<int>(minOpCount);
    }

private:
    size_t findIndex(std::vector<int> const &numbers, int value) const
    {
        size_t left = 0;
        size_t right = numbers.size() - 1;
        if (value >= numbers[right])
            return right;
        while ((right - left) > 1)
        {
            const size_t middle = (left + right) / 2;
            if (numbers[middle] == value)
                return middle;
            (numbers[middle] < value ? left : right) = middle;
        }
        return numbers[right] == value ? right : left;
    }
};

}

namespace MinimumOpNumberMakeArrayContinuousTask
{

TEST(MinimumOpNumberMakeArrayContinuousTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minOperations({4, 2, 5, 3}));
    ASSERT_EQ(1, solution.minOperations({1, 2, 3, 5, 6}));
    ASSERT_EQ(3, solution.minOperations({1, 10, 100, 1000}));
}

TEST(MinimumOpNumberMakeArrayContinuousTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({8, 5, 9, 9, 8, 4}));
}

}