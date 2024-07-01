#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool threeConsecutiveOdds(std::vector<int> const &arr) const
    {
        for (size_t index = 2; index < arr.size(); ++index)
        {
            if (((arr[index - 2] % 2) == 1) &&
                ((arr[index - 1] % 2) == 1) &&
                ((arr[index] % 2) == 1))
                return true;
        }
        return false;
    }
};

}

namespace ThreeConsecutiveOddsTask
{

TEST(ThreeConsecutiveOddsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.threeConsecutiveOdds({2, 6, 4, 1}));
    ASSERT_EQ(true, solution.threeConsecutiveOdds({1, 2, 34, 3, 4, 5, 7, 23, 12}));
}

}