#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPairs(std::vector<int> const &nums) const
    {
        size_t pairsCount = 0;
        for (size_t firstIndex = 0; firstIndex < nums.size(); ++firstIndex)
        {
            for (size_t secondIndex = firstIndex + 1; secondIndex < nums.size(); ++secondIndex)
            {
                if ((nums[firstIndex] == nums[secondIndex]) || isAlmostEqual(nums[firstIndex], nums[secondIndex]))
                    ++pairsCount;
            }
        }
        return static_cast<int>(pairsCount);
    }

private:
    [[nodiscard]] bool isAlmostEqual(int number1, int number2) const
    {
        int swapDigit1 = 0;
        int swapDigit2 = 0;
        int swapCount = 0;
        while ((number1 > 0) || (number2 > 0))
        {
            int digit1 = number1 % 10;
            int digit2 = number2 % 10;
            number1 /= 10;
            number2 /= 10;
            if (digit1 == digit2)
                continue;
            if (swapCount > 1)
                return false;
            if (swapCount == 1)
            {
                if ((digit1 != swapDigit2) || (digit2 != swapDigit1))
                    return false;
            }
            if (swapCount == 0)
            {
                swapDigit1 = digit1;
                swapDigit2 = digit2;
            }
            ++swapCount;
        }
        return swapCount != 1;
    }
};

}

namespace CountAlmostEqualPairs1Task
{

TEST(CountAlmostEqualPairs1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countPairs({3, 12, 30, 17, 21}));
    ASSERT_EQ(10, solution.countPairs({1, 1, 1, 1, 1}));
    ASSERT_EQ(0, solution.countPairs({123, 231}));
}

}