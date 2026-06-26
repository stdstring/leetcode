#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countMajoritySubarrays(std::vector<int> const &nums, int target) const
    {
        const size_t n = nums.size();
        size_t result = 0;
        size_t currentCount = n;
        size_t currentPrefixSum = 0;
        std::vector<size_t> prefixSums(2 * n + 1, 0);
        prefixSums[currentCount] = 1;
        for (const int number : nums)
        {
            if (number == target)
            {
                currentPrefixSum += prefixSums[currentCount];
                ++currentCount;
                ++prefixSums[currentCount];
            }
            else
            {
                --currentCount;
                currentPrefixSum -= prefixSums[currentCount];
                ++prefixSums[currentCount];
            }
            result += currentPrefixSum;
        }
        return static_cast<long long>(result);
    }
};

}

namespace CountSubarraysWithMajorityElement2Task
{

TEST(CountSubarraysWithMajorityElement2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countMajoritySubarrays({1, 2, 2, 3}, 2));
    ASSERT_EQ(10, solution.countMajoritySubarrays({1, 1, 1, 1}, 1));
    ASSERT_EQ(0, solution.countMajoritySubarrays({1, 2, 3}, 4));
}

}