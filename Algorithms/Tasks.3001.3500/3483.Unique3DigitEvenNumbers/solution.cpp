#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int totalNumbers(std::vector<int> const &digits) const
    {
        std::vector<size_t> digitFreq({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
        for (const int digit : digits)
            ++digitFreq[digit];
        size_t result = 0;
        for (int digit1 = 1; digit1 < 10; ++digit1)
        {
            if (digitFreq[digit1] == 0)
                continue;
            --digitFreq[digit1];
            for (int digit2 = 0; digit2 < 10; ++digit2)
            {
                if (digitFreq[digit2] == 0)
                    continue;
                --digitFreq[digit2];
                for (int digit3 = 0; digit3 < 10; digit3 += 2)
                {
                    if (digitFreq[digit3] > 0)
                        ++result;
                }
                ++digitFreq[digit2];
            }
            ++digitFreq[digit1];
        }
        return static_cast<int>(result);
    }
};

}

namespace Unique3DigitEvenNumbersTask
{

TEST(Unique3DigitEvenNumbersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.totalNumbers({1, 2, 3, 4}));
    ASSERT_EQ(2, solution.totalNumbers({0, 2, 2}));
    ASSERT_EQ(1, solution.totalNumbers({6, 6, 6}));
    ASSERT_EQ(0, solution.totalNumbers({1, 3, 5}));
}

}