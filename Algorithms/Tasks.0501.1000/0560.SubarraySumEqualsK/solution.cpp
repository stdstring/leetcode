#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subarraySum(std::vector<int> const &nums, int k) const
    {
        size_t subarrayCount = 0;
        int currentPrefix = 0;
        std::unordered_map<int, size_t> prefixCountMap;
        prefixCountMap.emplace(0, 1);
        for (const int number : nums)
        {
            currentPrefix += number;
            auto iterator = prefixCountMap.find(currentPrefix - k);
            if (iterator != prefixCountMap.cend())
               subarrayCount += (iterator->second);
            ++prefixCountMap[currentPrefix];
        }
        return static_cast<int>(subarrayCount);
    }
};

}

namespace SubarraySumEqualsKTask
{

TEST(SubarraySumEqualsKTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.subarraySum({1, 1, 1}, 2));
    ASSERT_EQ(2, solution.subarraySum({1, 2, 3}, 3));
}

TEST(SubarraySumEqualsKTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.subarraySum({1}, 0));
}

}