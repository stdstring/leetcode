#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subarraysWithKDistinct(std::vector<int> const &nums, int k) const
    {
        // Count of SubArrays with At Most K Distinct Elements = Count of SubArrays with K Distinct Elements + Count of SubArrays with At Most K-1 Distinct Elements
        return static_cast<int>(subarraysAtMostKDistinct(nums, k) - subarraysAtMostKDistinct(nums, k - 1));
    }

private:
    [[nodiscard]] size_t subarraysAtMostKDistinct(std::vector<int> const &nums, size_t maxDistinctCount) const
    {
        if (maxDistinctCount == 0)
            return 0;
        size_t subarraysCount = 0;
        std::unordered_map<int, size_t> subarrayNumbers;
        for (size_t start = 0, end = 0; end < nums.size();++end)
        {
            ++subarrayNumbers[nums[end]];
            while (subarrayNumbers.size() > maxDistinctCount)
            {
                const auto iterator = subarrayNumbers.find(nums[start]);
                --iterator->second;
                if (iterator->second == 0)
                    subarrayNumbers.erase(iterator);
                ++start;
            }
            subarraysCount += (end - start + 1);
        }
        return subarraysCount;
    }
};

}

namespace SubarraysWithKDifferentIntegersTask
{

TEST(SubarraysWithKDifferentIntegersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.subarraysWithKDistinct({1, 2, 1, 2, 3}, 2));
    ASSERT_EQ(3, solution.subarraysWithKDistinct({1, 2, 1, 3, 4}, 3));
}

}