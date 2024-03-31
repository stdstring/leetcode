#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long countAlternatingSubarrays(std::vector<int> const &nums) const
    {
        size_t result = 0;
        size_t start = 0;
        for (size_t end = 1; end < nums.size(); ++end)
        {
            if (nums[end] == nums[end - 1])
            {
                result += calcArithProgressionSum(end - start);
                start = end;
            }
        }
        result += calcArithProgressionSum(nums.size() - start);
        return static_cast<long long>(result);
    }

private:
    [[nodiscard]] size_t calcArithProgressionSum(size_t count) const
    {
        return (1 + count) * count / 2;
    }
};

}

namespace CountAlternatingSubarraysTask
{

TEST(CountAlternatingSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countAlternatingSubarrays({0, 1, 1, 1}));
    ASSERT_EQ(10, solution.countAlternatingSubarrays({1, 0, 1, 0}));
}

}