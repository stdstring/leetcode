#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long maximumSubarraySum(std::vector<int> const &nums, int k) const
    {
        const size_t subarraySize = k;
        long long maxSum = 0;
        std::unordered_set<int> subarrayNumbers;
        long long subarraySum = 0;
        size_t subarrayStart = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int number = nums[index];
            if (subarrayNumbers.count(number) == 0)
            {
                subarrayNumbers.insert(number);
                subarraySum += number;
                if (subarrayNumbers.size() == subarraySize)
                {
                    maxSum = std::max(maxSum, subarraySum);
                    subarrayNumbers.erase(nums[subarrayStart]);
                    subarraySum -= nums[subarrayStart];
                    ++subarrayStart;
                }
            }
            else
            {
                while (subarrayNumbers.count(number) != 0)
                {
                    subarrayNumbers.erase(nums[subarrayStart]);
                    subarraySum -= nums[subarrayStart];
                    ++subarrayStart;
                }
                subarrayNumbers.insert(number);
                subarraySum += number;
            }
        }
        if (subarrayNumbers.size() == subarraySize)
            maxSum = std::max(maxSum, subarraySum);
        return maxSum;
    }
};

}

namespace MaxSumDistinctSubarraysLengthKTask
{

TEST(MaxSumDistinctSubarraysLengthKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.maximumSubarraySum({1, 5, 4, 2, 9, 9, 9}, 3));
    ASSERT_EQ(0, solution.maximumSubarraySum({4, 4, 4}, 3));
}

TEST(MaxSumDistinctSubarraysLengthKTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maximumSubarraySum({3, 2, 3, 1}, 3));
}

}