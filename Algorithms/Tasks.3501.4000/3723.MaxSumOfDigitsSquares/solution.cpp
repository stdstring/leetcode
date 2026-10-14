#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string maxSumOfSquares(int num, int sum) const
    {
        // 1 : 81 / 1 = 81, 1 * 81 = 81
        // 2 : 81 / 4 = 20.25, 2 * 20.25 = 40.5
        // 3 : 81 / 9 = 9, 3 * 9 = 27
        // 4 : 81 / 16 = 5.0625, 4 * 5.0625 = 20.25
        // 5 : 81 / 25 = 3.24, 5 * 3.24 = 16.2
        // 6 : 81 / 36 = 2.25, 6 * 2.25 = 13.5
        // 7 : 81 / 49 = 1.653, 7 * 1.653 = 11.571
        // 8 : 81 / 64 = 1.265625, 8 * 1.265625 = 10.125
        std::string result(num, '0');
        for (size_t index = 0; index < result.size(); ++index)
        {
            const int digit = sum >= 9 ? 9 : sum;
            sum -= digit;
            result[index] = static_cast<char>('0' + digit);
        }
        return (sum == 0) ? result : "";
    }
};

}

namespace MaxSumOfDigitsSquaresTask
{

TEST(MaxSumOfDigitsSquaresTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("30", solution.maxSumOfSquares(2, 3));
    ASSERT_EQ("98", solution.maxSumOfSquares(2, 17));
    ASSERT_EQ("", solution.maxSumOfSquares(1, 10));
}

}