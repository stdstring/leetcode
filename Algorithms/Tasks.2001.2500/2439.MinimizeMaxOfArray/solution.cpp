#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizeArrayValue(std::vector<int> const &nums) const
    {
        int minMaxValue = nums[0];
        long long sum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            sum += nums[index];
            const long long count = static_cast<long long>(1 + index);
            int currentMaxValue = static_cast<int>(sum / count + (sum % count > 0 ? 1 : 0));
            minMaxValue = std::max(minMaxValue, currentMaxValue);
        }
        return minMaxValue;
    }
};

}

namespace MinimizeMaxOfArrayTask
{

TEST(MinimizeMaxOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minimizeArrayValue({3, 7, 1, 6}));
    ASSERT_EQ(10, solution.minimizeArrayValue({10, 1}));
}

}