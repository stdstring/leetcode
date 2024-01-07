#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countSubarrays(std::vector<int> const &nums, int k) const
    {
        const size_t minTimes = k;
        const int maxElement = *std::ranges::max_element(nums);
        std::vector<size_t> indices;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == maxElement)
                indices.emplace_back(index);
        }
        size_t result = 0;
        for (size_t slidingWindowEnd = minTimes - 1; slidingWindowEnd < indices.size(); ++slidingWindowEnd)
        {
            const size_t slidingWindowStart = slidingWindowEnd + 1 - minTimes;
            const size_t casesBefore = indices[slidingWindowStart] - (slidingWindowStart > 0 ? indices[slidingWindowStart - 1] : 0) + (slidingWindowStart > 0 ? 0 :1);
            const size_t casesAfter = nums.size() - indices[slidingWindowEnd];
            result += casesBefore * casesAfter;
        }
        return static_cast<long long>(result);
    }
};

}

namespace CountSubarraysWithMaxElementsTask
{

TEST(CountSubarraysWithMaxElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.countSubarrays({1, 3, 2, 3, 3}, 2));
    ASSERT_EQ(0, solution.countSubarrays({1, 4, 2, 1}, 3));
}

}