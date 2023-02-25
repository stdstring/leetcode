#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maxCount(int m, int n, std::vector<std::vector<int>> const &ops) const
    {
        int bestRow = m;
        int bestColumn = n;
        for (std::vector<int> const &op : ops)
        {
            bestRow = std::min(bestRow, op[0]);
            bestColumn = std::min(bestColumn, op[1]);
        }
        return bestRow * bestColumn;
    }
};

}

namespace RangeAdditionIITask
{

TEST(RangeAdditionIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.maxCount(3, 3, {{2, 2}, {3, 3}}));
    ASSERT_EQ(4, solution.maxCount(3, 3, {{2, 2}, {3, 3}, {3, 3}, {3, 3}, {2, 2}, {3, 3}, {3, 3}, {3, 3}, {2, 2}, {3, 3}, {3, 3}, {3, 3}}));
    ASSERT_EQ(9, solution.maxCount(3, 3, {}));
}

}
