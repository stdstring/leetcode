#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int rangeSum(std::vector<int> const &nums, int n, int left, int right) const
    {
        const size_t totalSize = nums.size() * (1 + nums.size()) / 2;
        std::vector<int> dest;
        dest.reserve(totalSize);
        for (size_t fromIndex = 0; fromIndex < nums.size(); ++fromIndex)
        {
            int sum = 0;
            for (size_t toIndex = fromIndex; toIndex < nums.size(); ++toIndex)
            {
                sum += nums[toIndex];
                dest.emplace_back(sum);
            }
        }
        std::ranges::sort(dest);
        long long result = 0;
        // because indexed from 1
        for (int index = left; index <= right; ++index)
            result += dest[index - 1];
        return static_cast<int>(result % 1000000007);
    }
};

}

namespace RangeSumOfSortedSubarraySumsTask
{

TEST(RangeSumOfSortedSubarraySumsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.rangeSum({1, 2, 3, 4}, 4, 1, 5));
    ASSERT_EQ(6, solution.rangeSum({1, 2, 3, 4}, 4, 3, 4));
    ASSERT_EQ(50, solution.rangeSum({1, 2, 3, 4}, 4, 1, 10));
}

}