#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long coloredCells(int n) const
    {
        switch (n)
        {
        case 1:
            return 1LL;
        case 2:
            return 5LL;
        default:
            const long long minutes = n;
            return 1LL + 4 * (minutes - 1) + 4 * (1 + (minutes - 2)) * (minutes - 2) / 2;
        }
    }
};

}

namespace CountTotalNumberColoredCellsTask
{

TEST(CountTotalNumberColoredCellsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.coloredCells(1));
    ASSERT_EQ(5, solution.coloredCells(2));
}

TEST(CountTotalNumberColoredCellsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.coloredCells(3));
    ASSERT_EQ(25, solution.coloredCells(4));
    ASSERT_EQ(181, solution.coloredCells(10));
    ASSERT_EQ(19801, solution.coloredCells(100));
    ASSERT_EQ(885781, solution.coloredCells(666));
}

}