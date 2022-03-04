#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    double champagneTower(int poured, int queryRow, int queryGlass) const
    {
        std::vector<double> current;
        std::vector<double> next({1.0 * poured});
        for (size_t row = 0; row <= static_cast<size_t>(queryRow); ++row)
        {
            std::swap(current, next);
            next.push_back(0);
            next.push_back(0);
            next[0] = 0;
            for (size_t column = 0; column <= row; ++column)
            {
                next[column + 1] = 0;
                if (current[column] > 1)
                {
                    const double overflow = (current[column] - 1) / 2;
                    next[column] += overflow;
                    next[column + 1] = overflow;
                    current[column] = 1;
                }
            }
        }
        return current[queryGlass];
    }
};

}

namespace ChampagneTowerTask
{

TEST(ChampagneTowerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(0.0, solution.champagneTower(1, 1, 1));
    ASSERT_DOUBLE_EQ(0.5, solution.champagneTower(2, 1, 1));
    ASSERT_DOUBLE_EQ(1.0, solution.champagneTower(100000009, 33, 17));
}

}