#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subarraysDivByK(std::vector<int> const &nums, int k) const
    {
        std::unordered_map<int, size_t> prefixSumRestMap;
        int prefixSum = 0;
        for (const int number : nums)
        {
            prefixSum += number;
            int rest = prefixSum % k;
            if (rest < 0)
                rest += k;
            ++prefixSumRestMap[rest];
        }
        size_t result = 0;
        for (auto const &[rest, restCount] : prefixSumRestMap)
            result += calcSubarraysCount(rest == 0 ? restCount + 1 : restCount);
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] size_t calcSubarraysCount(size_t restCount) const
    {
        return restCount * (restCount - 1) / 2;
    }
};

}

namespace SubarraySumsDivisibleByKTask
{

TEST(SubarraySumsDivisibleByKTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.subarraysDivByK({4, 5, 0, -2, -3, 1}, 5));
    ASSERT_EQ(0, solution.subarraysDivByK({5}, 9));
}

}