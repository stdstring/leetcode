#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfSubarrays(std::vector<int> const &arr, int k, int threshold) const
    {
        int subarraySum = 0;
        // init
        for (size_t index = 0; index < static_cast<size_t>(k); ++index)
            subarraySum += arr[index];
        int result = subarraySum / k >= threshold ? 1 : 0;
        // traverse
        for (size_t index = k; index < arr.size(); ++index)
        {
            subarraySum -= arr[index - k];
            subarraySum += arr[index];
            if ((subarraySum / k) >= threshold)
                ++result;
        }
        return result;
    }
};

}

namespace NumberSubArraysWithAverageGTEThresholdTask
{

TEST(NumberSubArraysWithAverageGTEThresholdTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numOfSubarrays({2, 2, 2, 2, 5, 5, 5, 8}, 3, 4));
    ASSERT_EQ(6, solution.numOfSubarrays({11, 13, 17, 23, 29, 31, 7, 5, 2, 3}, 3, 5));
}

}