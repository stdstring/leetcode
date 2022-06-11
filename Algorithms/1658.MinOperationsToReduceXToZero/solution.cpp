#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums, int x) const
    {
        std::unordered_map<int, size_t> suffixMap;
        size_t opCount = INT_MAX;
        int suffixSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            suffixSum += nums[nums.size() - 1 - index];
            if (suffixSum > x)
                break;
            if (suffixSum == x)
            {
                opCount = index + 1;
                break;
            }
            suffixMap[suffixSum] = index + 1;
        }
        int prefixSum = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            prefixSum += nums[index];
            if (prefixSum > x)
                break;
            if (prefixSum == x)
            {
                opCount = std::min(opCount, index + 1);
                break;
            }
            auto iterator = suffixMap.find(x - prefixSum);
            if (iterator != suffixMap.cend())
            {
                size_t currentOpCount = index + 1 + iterator->second;
                if (currentOpCount <= nums.size())
                    opCount = std::min(opCount, currentOpCount);
            }
        }
        return opCount == INT_MAX ? -1 : static_cast<int>(opCount);
    }
};

}

namespace MinOperationsToReduceXToZeroTask
{

TEST(MinOperationsToReduceXToZeroTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minOperations({1, 1, 4, 2, 3}, 5));
    ASSERT_EQ(-1, solution.minOperations({5, 6, 7, 8, 9}, 4));
    ASSERT_EQ(5, solution.minOperations({3, 2, 20, 1, 1, 3}, 10));
}

TEST(MinOperationsToReduceXToZeroTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minOperations({5, 2, 3, 1, 1}, 5));
    ASSERT_EQ(-1, solution.minOperations({1, 1}, 3));
}

}