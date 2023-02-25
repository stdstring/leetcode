#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getSumAbsoluteDifferences(std::vector<int> const &nums) const
    {
        std::vector<int> prefixSum(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
            prefixSum[index] = (index > 0 ? prefixSum[index - 1] : 0) + nums[index];
        std::vector<int> result(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int countBefore = static_cast<int>(index);
            const int countAfter = static_cast<int>(nums.size() - 1 - index);
            result[index] = (index > 0 ? countBefore * nums[index] - prefixSum[index - 1] : 0) +
                            (prefixSum.back() - prefixSum[index] - countAfter * nums[index]);
        }
        return result;
    }
};

}

namespace SumOfAbsoluteDiffInSortedArrayTask
{

TEST(SumOfAbsoluteDiffInSortedArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 3, 5}), solution.getSumAbsoluteDifferences({2, 3, 5}));
    ASSERT_EQ(std::vector<int>({24, 15, 13, 15, 21}), solution.getSumAbsoluteDifferences({1, 4, 6, 8, 10}));
}

}