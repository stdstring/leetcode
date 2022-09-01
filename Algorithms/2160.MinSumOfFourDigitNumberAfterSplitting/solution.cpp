#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSum(int num) const
    {
        const int digit0 = num % 10;
        const int digit1 = (num / 10) % 10;
        const int digit2 = (num / 100) % 10;
        const int digit3 = num / 1000;
        std::vector<int> digits({digit0, digit1, digit2, digit3});
        std::sort(digits.begin(), digits.end());
        return 10 * (digits[0] + digits[1]) + digits[2] + digits[3];
    }
};

}

namespace MinSumOfFourDigitNumberAfterSplittingTask
{

TEST(MinSumOfFourDigitNumberAfterSplittingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(52, solution.minimumSum(2932));
    ASSERT_EQ(13, solution.minimumSum(4009));
}

}