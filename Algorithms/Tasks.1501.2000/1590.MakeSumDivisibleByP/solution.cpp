#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSubarray(std::vector<int> const &nums, int p) const
    {
        std::vector<int> prefixRest(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int currentRest = (nums[index] + (index > 0 ? prefixRest[index - 1] : 0)) % p;
            prefixRest[index] = currentRest;
        }
        const int totalRest = prefixRest.back();
        if (totalRest == 0)
            return 0;
        if (nums.size() == 1)
            return -1;
        size_t minRemovedSize = nums.size();
        std::unordered_map<int, size_t> restMap;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (prefixRest[index] == 0)
                minRemovedSize = std::min(minRemovedSize, nums.size() - 1 - index);
            if (prefixRest[index] == totalRest)
                minRemovedSize = std::min(minRemovedSize, index + 1);
            const int restBefore = (prefixRest[index] - totalRest + p) % p;
            auto iterator = restMap.find(restBefore);
            if (iterator != restMap.cend())
                minRemovedSize = std::min(minRemovedSize, index - iterator->second);
            restMap[prefixRest[index]] = index;
        }
        return minRemovedSize == nums.size() ? -1 : static_cast<int>(minRemovedSize);
    }
};

}

namespace MakeSumDivisibleByPTask
{

TEST(MakeSumDivisibleByPTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSubarray({3, 1, 4, 2}, 6));
    ASSERT_EQ(2, solution.minSubarray({6, 3, 5, 2}, 9));
    ASSERT_EQ(0, solution.minSubarray({1, 2, 3}, 3));
}

TEST(MakeSumDivisibleByPTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minSubarray({1}, 1));
    ASSERT_EQ(7, solution.minSubarray({8, 32, 31, 18, 34, 20, 21, 13, 1, 27, 23, 22, 11, 15, 30, 4, 2}, 148));
}

}