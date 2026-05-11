#include <ranges>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> separateDigits(std::vector<int> const &nums) const
    {
        std::vector<int> result;
        result.reserve(nums.size() * MaxDigitCount);
        for (const int number : nums)
        {
            for (int digit : getReversedDigits(number) | std::views::reverse)
                result.emplace_back(digit);
        }
        return result;
    }

private:
    static constexpr size_t MaxDigitCount = 6;

    [[nodiscard]] std::vector<int> getReversedDigits(int number) const
    {
        std::vector<int> digits;
        digits.reserve(MaxDigitCount);
        for (;number != 0; number /= 10)
            digits.emplace_back(number % 10);
        return digits;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 2, 5, 8, 3, 7, 7}), solution.separateDigits({13, 25, 83, 77}));
    ASSERT_EQ(std::vector<int>({7, 1, 3, 9}), solution.separateDigits({7, 1, 3, 9}));
}

}