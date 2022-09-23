#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long zeroFilledSubarray(std::vector<int> const &nums) const
    {
        long long result = 0;
        size_t start = 0;
        for (size_t end = 0; end < nums.size(); ++end)
        {
            if (nums[end] != 0)
            {
                result += calcArithProgressionSum(static_cast<long long>(end - start));
                start = end + 1;
            }
        }
        return result + calcArithProgressionSum(static_cast<long long>(nums.size() - start));
    }

private:
    [[nodiscard]] long long calcArithProgressionSum(long long n) const
    {
        return (1 + n) * n / 2;
    }
};

}

namespace NumberOfZeroFilledSubarraysTask
{

TEST(NumberOfZeroFilledSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.zeroFilledSubarray({1, 3, 0, 0, 2, 0, 0, 4}));
    ASSERT_EQ(9, solution.zeroFilledSubarray({0, 0, 0, 2, 0, 0}));
    ASSERT_EQ(0, solution.zeroFilledSubarray({2, 10, 2019}));
}

}