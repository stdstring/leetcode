#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> resultsArray(std::vector<int> const &nums, int k) const
    {
        const size_t subarraySize = k;
        if (subarraySize == 1)
            return nums;
        std::vector<int> result(nums.size() - subarraySize + 1, -1);
        size_t badPartSize = 0;
        // prepare sliding window
        for (size_t index = 1; index < subarraySize; ++index)
        {
            if (nums[index] != (nums[index - 1] + 1))
                badPartSize = index;
        }
        if (badPartSize == 0)
            result[0] = nums[subarraySize - 1];
        // move sliding window
        for (size_t index = subarraySize; index < nums.size(); ++index)
        {
            if (nums[index] == (nums[index - 1] + 1))
            {
                if (badPartSize > 0)
                    --badPartSize;
                if (badPartSize == 0)
                    result[index - subarraySize + 1] = nums[index];
            }
            else
                badPartSize = subarraySize - 1;
        }
        return result;
    }
};

}

namespace FindPowerKSizeSubarrays2Task
{

TEST(FindPowerKSizeSubarrays2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 4, -1, -1, -1}), solution.resultsArray({1, 2, 3, 4, 3, 2, 5}, 3));
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.resultsArray({2, 2, 2, 2, 2}, 4));
    ASSERT_EQ(std::vector<int>({-1, 3, -1, 3, -1}), solution.resultsArray({3, 2, 3, 2, 3, 2}, 2));
}

}