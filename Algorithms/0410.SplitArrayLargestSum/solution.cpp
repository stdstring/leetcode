#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int splitArrayViaDynamicProgramming(std::vector<int> const &nums, int m) const
    {
        std::vector<std::vector<int>> data(nums.size(), std::vector<int>(0LL + m + 1, INT_MAX));
        std::vector<int> prefixSum(nums.size() + 1, 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixSum[index + 1] = prefixSum[index] + nums[index];
        for (int subarraysCount = 1; subarraysCount <= m; ++subarraysCount)
        {
            for (size_t fromIndex = 0; fromIndex < nums.size(); ++fromIndex)
            {
                if (subarraysCount == 1)
                {
                    data[fromIndex][subarraysCount] = prefixSum[nums.size()] - prefixSum[fromIndex];
                    continue;
                }
                for (size_t toIndex = fromIndex; toIndex <= nums.size() - subarraysCount; ++toIndex)
                {
                    int currentSum = prefixSum[toIndex + 1] - prefixSum[fromIndex];
                    int largestSum = std::max(currentSum, data[toIndex + 1][0LL + subarraysCount - 1]);
                    data[fromIndex][subarraysCount] = std::min(data[fromIndex][subarraysCount], largestSum);
                }
            }
        }
        return data[0][m];
    }

    [[nodiscard]] int splitArrayViaBinarySearch(std::vector<int> const &nums, int m) const
    {
        const int totalSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        const int maxElement = *std::max_element(nums.cbegin(), nums.cend());
        int left = maxElement;
        int right = totalSum;
        while (left <= right)
        {
            const int middle = (left + right) / 2;
            if (minimumSubarraysRequired(nums, middle) <= m)
                right = middle - 1;
            else
                left = middle + 1;
        }
        return left;
    }

private:
    [[nodiscard]] int minimumSubarraysRequired(std::vector<int> const &nums, int maxSumAllowed) const
    {
        int subarraysCount = 1;
        int currentSum = 0;
        for (const int number : nums)
        {
            if (currentSum + number > maxSumAllowed)
            {
                ++subarraysCount;
                currentSum = number;
            }
            else
                currentSum += number;
        }
        return subarraysCount;
    }
};

}

namespace
{

void checkSplitArray(std::vector<int> const &nums, int m, int expectedResult)
{
    const Solution solution;
    ASSERT_EQ(expectedResult, solution.splitArrayViaDynamicProgramming(nums, m));
    ASSERT_EQ(expectedResult, solution.splitArrayViaBinarySearch(nums, m));
}

}

namespace SplitArrayLargestSumTask
{

TEST(SplitArrayLargestSumTaskTests, Examples)
{
    checkSplitArray({7, 2, 5, 10, 8}, 2, 18);
    checkSplitArray({1, 2, 3, 4, 5}, 2, 9);
    checkSplitArray({1, 4, 4}, 3, 4);
}

}
