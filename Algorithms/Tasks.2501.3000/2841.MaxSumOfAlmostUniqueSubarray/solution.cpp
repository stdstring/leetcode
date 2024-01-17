#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maxSum(std::vector<int> const &nums, int m, int k) const
    {
        const size_t minDistinctCount = m;
        const size_t subarraySize = k;
        std::unordered_map<int, size_t> numberMap;
        long long subarraySum = 0;
        // init
        for (size_t index = 0; index < subarraySize; ++index)
        {
            ++numberMap[nums[index]];
            subarraySum += nums[index];
        }
        // calc
        long long maxSubarraySum = numberMap.size() >= minDistinctCount ? subarraySum : 0;
        for (size_t index = subarraySize; index < nums.size(); ++index)
        {
            ++numberMap[nums[index]];
            removeNumber(numberMap, nums[index - subarraySize]);
            subarraySum += nums[index];
            subarraySum -= nums[index - subarraySize];
            if (numberMap.size() >= minDistinctCount)
                maxSubarraySum = std::max(maxSubarraySum, subarraySum);
        }
        return maxSubarraySum;
    }

private:
    void removeNumber(std::unordered_map<int, size_t> &numberMap, int number) const
    {
        const auto iterator = numberMap.find(number);
        --iterator->second;
        if (iterator->second == 0)
            numberMap.erase(iterator);
    }
};

}

namespace MaxSumOfAlmostUniqueSubarrayTask
{

TEST(MaxSumOfAlmostUniqueSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.maxSum({2, 6, 7, 3, 1, 7}, 3, 4));
    ASSERT_EQ(23, solution.maxSum({5, 9, 9, 2, 4, 5, 4}, 1, 3));
    ASSERT_EQ(0, solution.maxSum({1, 2, 1, 2, 1, 2, 1}, 3, 3));
}

}