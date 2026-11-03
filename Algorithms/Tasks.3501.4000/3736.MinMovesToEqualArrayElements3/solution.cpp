#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMoves(std::vector<int> const &nums) const
    {
        const int maxValue = std::ranges::max(nums);
        int result = 0;
        for (const int number : nums)
            result += (maxValue - number);
        return result;
    }
};

}

namespace MinMovesToEqualArrayElements3Task
{

TEST(MinMovesToEqualArrayElements3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minMoves({2, 1, 3}));
    ASSERT_EQ(2, solution.minMoves({4, 4, 5}));
}

}