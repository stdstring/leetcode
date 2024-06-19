#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countDistinct(std::vector<int> const &nums, int k, int p) const
    {
        const size_t maxDivisibleCount = k;
        // for calculating rolling hash
        const long long pValue = 3571;
        const long long mValue = 100000000019;
        std::unordered_set<long long> knownSubarrays;
        size_t subarraysCount = 0;
        for (size_t startIndex = 0; startIndex < nums.size(); ++startIndex)
        {
            long long hash = 0;
            long long powerValue = 1;
            size_t divisibleCount = 0;
            for (size_t endIndex = startIndex; endIndex < nums.size(); ++endIndex)
            {
                if ((nums[endIndex] % p) == 0)
                    ++divisibleCount;
                if (divisibleCount > maxDivisibleCount)
                    break;
                hash = (hash + nums[endIndex] * powerValue) % mValue;
                powerValue = (powerValue * pValue) % mValue;
                if (knownSubarrays.contains(hash))
                    continue;
                ++subarraysCount;
                knownSubarrays.emplace(hash);
            }
        }
        return static_cast<int>(subarraysCount);
    }
};

}

namespace KDivisibleElementsSubarraysTask
{

TEST(KDivisibleElementsSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.countDistinct({2, 3, 3, 2, 2}, 2, 2));
    ASSERT_EQ(10, solution.countDistinct({1, 2, 3, 4}, 4, 1));
}

}