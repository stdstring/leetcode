#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumAverageDifference(std::vector<int> const &nums) const
    {
        size_t bestIndex = nums.size();
        long long minDiff = INT_MAX;
        long long prefixSum = 0;
        long long suffixSum = std::accumulate(nums.cbegin(), nums.cend(), 0LL);
        const size_t maxIndex = nums.size() - 1;
        for (size_t index = 0; index <= maxIndex; ++index)
        {
            prefixSum += nums[index];
            suffixSum -= nums[index];
            const int prefixLength = static_cast<int>(index + 1);
            const int suffixLength = static_cast<int>(index < maxIndex ? maxIndex - index : 1);
            const long long currentDiff = std::abs(prefixSum / prefixLength - suffixSum / suffixLength);
            if (currentDiff < minDiff)
            {
                minDiff = currentDiff;
                bestIndex = index;
            }
        }
        return static_cast<int>(bestIndex);
    }
};

}

namespace MinAverageDifferenceTask
{

TEST(MinAverageDifferenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumAverageDifference({2, 5, 3, 9, 5, 3}));
    ASSERT_EQ(0, solution.minimumAverageDifference({0}));
}

}