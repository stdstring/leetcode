#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int heightChecker(std::vector<int> const &heights) const
    {
        std::vector<int> expected(heights);
        std::ranges::sort(expected);
        size_t unexpectedCount = 0;
        for (size_t index = 0; index < heights.size(); ++index)
        {
            if (heights[index] != expected[index])
                ++unexpectedCount;
        }
        return static_cast<int>(unexpectedCount);
    }
};

}

namespace HeightCheckerTask
{

TEST(HeightCheckerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.heightChecker({1, 1, 4, 2, 1, 3}));
    ASSERT_EQ(5, solution.heightChecker({5, 1, 2, 3, 4}));
    ASSERT_EQ(0, solution.heightChecker({1, 2, 3, 4, 5}));
}

}