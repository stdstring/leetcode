#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool kLengthApart(std::vector<int> const &nums, int k) const
    {
        const size_t minDistance = k;
        size_t prev = nums.size();
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == 0)
                continue;
            if ((prev < index) && ((index - prev) <= minDistance))
                return false;
            prev = index;
        }
        return true;
    }
};

}

namespace CheckIfAll1AtLeastLengthKPlacesAwayTask
{

TEST(CheckIfAll1AtLeastLengthKPlacesAwayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.kLengthApart({1, 0, 0, 0, 1, 0, 0, 1}, 2));
    ASSERT_EQ(false, solution.kLengthApart({1, 0, 0, 1, 0, 1}, 2));
}

}