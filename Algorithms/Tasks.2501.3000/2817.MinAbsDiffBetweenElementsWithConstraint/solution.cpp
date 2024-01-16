#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minAbsoluteDifference(std::vector<int> const &nums, int x) const
    {
        const size_t shift = x;
        std::map<int, size_t> numberMap;
        // init
        for (size_t index = shift - 1; index < nums.size(); ++index)
            ++numberMap[nums[index]];
        int minAbsDiff = INT_MAX;
        // move
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (index >= shift)
                ++numberMap[nums[index - shift]];
            if ((index + shift - 1) < nums.size())
                removeNumber(numberMap, nums[index + shift - 1]);
            auto iterator = numberMap.lower_bound(nums[index]);
            if (iterator != numberMap.cend())
                minAbsDiff = std::min(iterator->first - nums[index], minAbsDiff);
            if (iterator == numberMap.cbegin())
                continue;
            iterator = std::prev(iterator, 1);
            minAbsDiff = std::min(nums[index] - iterator->first, minAbsDiff);
        }
        return minAbsDiff;
    }

private:
    void removeNumber(std::map<int, size_t> &numberMap, int number) const
    {
        const auto iterator = numberMap.find(number);
        --iterator->second;
        if (iterator->second == 0)
            numberMap.erase(iterator);
    }
};

}

namespace MinAbsDiffBetweenElementsWithConstraintTask
{

TEST(MinAbsDiffBetweenElementsWithConstraintTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minAbsoluteDifference({4, 3, 2, 4}, 2));
    ASSERT_EQ(1, solution.minAbsoluteDifference({5, 3, 2, 10, 15}, 1));
    ASSERT_EQ(3, solution.minAbsoluteDifference({1, 2, 3, 4}, 3));
}

}