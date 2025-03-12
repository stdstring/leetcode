#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumCount(std::vector<int> const &nums) const
    {
        size_t negativeCount = 0;
        size_t positiveCount = 0;
        for (int number : nums)
        {
            if (number < 0)
                ++negativeCount;
            if (number > 0)
                ++positiveCount;
        }
        return static_cast<int>(std::max(negativeCount, positiveCount));
    }
};

}

namespace MaxCountPositiveNegativeIntegerTask
{

TEST(MaxCountPositiveNegativeIntegerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumCount({-2, -1, -1, 1, 2, 3}));
    ASSERT_EQ(3, solution.maximumCount({-3, -2, -1, 0, 0, 1, 2}));
    ASSERT_EQ(4, solution.maximumCount({5, 20, 66, 1314}));
}

}