#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findNumbers(std::vector<int> const &nums) const
    {
        size_t result = 0;
        for (const int number : nums)
        {
            if (((10 <= number) && (number <= 99)) ||
                ((1000 <= number) && (number <= 9999)) ||
                ((100000 <= number) && (number <= 999999)) ||
                ((10000000 <= number) && (number <= 99999999)) ||
                (1000000000 <= number))
            ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace FindNumbersWithEvenNumberDigitsTask
{

TEST(FindNumbersWithEvenNumberDigitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findNumbers({12, 345, 2, 6, 7896}));
    ASSERT_EQ(1, solution.findNumbers({555, 901, 482, 1771}));
}

}