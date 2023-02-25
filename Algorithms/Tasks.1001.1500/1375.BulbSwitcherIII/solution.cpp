#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numTimesAllBlue(std::vector<int> const &light) const
    {
        int maxValue = 0;
        size_t result = 0;
        for (int position = 1; position <= static_cast<int>(light.size()); ++position)
        {
            maxValue = std::max(maxValue, light[position - 1]);
            if (maxValue == position)
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace BulbSwitcherIIITask
{

TEST(BulbSwitcherIIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numTimesAllBlue({2, 1, 3, 5, 4}));
    ASSERT_EQ(2, solution.numTimesAllBlue({3, 2, 4, 1, 5}));
    ASSERT_EQ(1, solution.numTimesAllBlue({4, 1, 2, 3}));
    ASSERT_EQ(3, solution.numTimesAllBlue({2, 1, 4, 3, 6, 5}));
    ASSERT_EQ(6, solution.numTimesAllBlue({1, 2, 3, 4, 5, 6}));
}

}