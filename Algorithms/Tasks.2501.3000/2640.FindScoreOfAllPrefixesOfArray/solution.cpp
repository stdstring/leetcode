#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> findPrefixScore(std::vector<int> const &nums) const
    {
        std::vector<long long> result(nums.size(), 0);
        int maxValue = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            maxValue = std::max(maxValue, nums[index]);
            const long long conversionValue = 1LL * nums[index] + maxValue;
            result[index] = (index > 0 ? result[index - 1] : 0) + conversionValue;
        }
        return result;
    }
};

}

namespace FindScoreOfAllPrefixesOfArrayTask
{

TEST(FindScoreOfAllPrefixesOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({4, 10, 24, 36, 56}), solution.findPrefixScore({2, 3, 7, 5, 10}));
    ASSERT_EQ(std::vector<long long>({2, 4, 8, 16, 32, 64}), solution.findPrefixScore({1, 1, 2, 4, 8, 16}));
}

}