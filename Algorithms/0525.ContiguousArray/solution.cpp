#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMaxLength(std::vector<int> const &nums) const
    {
        size_t maxSubarrayLength = 0;
        std::unordered_map<int, size_t> prefixBalanceMap;
        int balance = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            balance += (nums[index] == 0 ? -1 : 1);
            auto iterator = prefixBalanceMap.find(balance);
            if (iterator == prefixBalanceMap.end())
                prefixBalanceMap.emplace(balance, index);
            else
                maxSubarrayLength = std::max(maxSubarrayLength, index - iterator->second);
            if (balance == 0)
                maxSubarrayLength = index + 1;
        }
        return static_cast<int>(maxSubarrayLength);
    }
};

}

namespace ContiguousArrayTask
{

TEST(ContiguousArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findMaxLength({0, 1}));
    ASSERT_EQ(2, solution.findMaxLength({0, 1, 0}));
}

TEST(ContiguousArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findMaxLength({0, 1, 1}));
    ASSERT_EQ(68, solution.findMaxLength({0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1,
                                          0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0,
                                          0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
                                          0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
                                          0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1}));
}

}