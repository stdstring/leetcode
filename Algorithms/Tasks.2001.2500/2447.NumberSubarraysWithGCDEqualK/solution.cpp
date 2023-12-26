#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subarrayGCD(std::vector<int> const &nums, int k) const
    {
        size_t subarrayCount = 0;
        for (size_t start = 0; start < nums.size(); ++start)
        {
            int gcd = nums[start];
            for (size_t size = 1; (start + size) <= nums.size(); ++size)
            {
                gcd = std::gcd(gcd, nums[start + size - 1]);
                if (gcd == k)
                    ++subarrayCount;
                if (gcd < k)
                    break;
            }
        }
        return static_cast<int>(subarrayCount);
    }
};

}

namespace NumberSubarraysWithGCDEqualKTask
{

TEST(NumberSubarraysWithGCDEqualKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.subarrayGCD({9, 3, 1, 2, 6, 3}, 3));
    ASSERT_EQ(0, solution.subarrayGCD({4}, 7));
}

}