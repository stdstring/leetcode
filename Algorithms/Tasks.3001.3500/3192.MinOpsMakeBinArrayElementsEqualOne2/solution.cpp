#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums) const
    {
        int flipCount = 0;
        int flipResult = 0;
        for (const int number : nums)
        {
            const int current = (number + flipResult) % 2;
            if (current == 0)
            {
                ++flipCount;
                ++flipResult;
            }
        }
        return flipCount;
    }
};

}

namespace MinOpsMakeBinArrayElementsEqualOne2Task
{

TEST(MinOpsMakeBinArrayElementsEqualOne2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minOperations({0, 1, 1, 0, 1}));
    ASSERT_EQ(1, solution.minOperations({1, 0, 0, 0}));
}

}