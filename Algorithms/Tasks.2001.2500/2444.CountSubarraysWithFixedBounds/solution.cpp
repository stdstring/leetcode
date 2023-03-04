#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countSubarrays(std::vector<int> const &nums, int minK, int maxK) const
    {
        const size_t npos = nums.size();
        long long result = 0;
        size_t lastMin = npos;
        size_t lastMax = npos;
        size_t leftBound = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if ((minK <= nums[index]) && (nums[index] <= maxK))
            {
                lastMin = minK == nums[index] ? index : lastMin;
                lastMax = maxK == nums[index] ? index : lastMax;
                if ((lastMin != npos) && (lastMax != npos))
                    result += static_cast<long long>(std::min(lastMin, lastMax) - leftBound + 1);
            }
            else
            {
                leftBound = index + 1;
                lastMin = npos;
                lastMax = npos;
            }
        }
        return result;
    }
};

}

namespace CountSubarraysWithFixedBoundsTask
{

TEST(CountSubarraysWithFixedBoundsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countSubarrays({1, 3, 5, 2, 7, 5}, 1, 5));
    ASSERT_EQ(10, solution.countSubarrays({1, 1, 1, 1}, 1, 1));
}

}