#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countArrangement(int n) const
    {
        return static_cast<int>(countArrangement(n, n, 0));
    }

private:
    [[nodiscard]] size_t countArrangement(int current, int n, int usageMask) const
    {
        if (current == 1)
            return 1;
        size_t result = 0;
        for (int pos = 1; pos <= n; ++pos)
        {
            const int mask = 1 << (pos - 1);
            if ((usageMask & mask) > 0)
                continue;
            if (((current % pos) != 0) && ((pos % current) != 0))
                continue;
            result += countArrangement(current - 1, n, usageMask | mask);
        }
        return result;
    }
};

}

namespace BeautifulArrangementTask
{

TEST(BeautifulArrangementTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countArrangement(2));
    ASSERT_EQ(1, solution.countArrangement(1));
}

TEST(BeautifulArrangementTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(700, solution.countArrangement(10));
    ASSERT_EQ(4010, solution.countArrangement(12));
    ASSERT_EQ(24679, solution.countArrangement(15));
}

}
