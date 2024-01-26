#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canSortArray(std::vector<int> const &nums) const
    {
        int prevMax = 0;
        int currentGroupBit1Count = 0;
        int currentMax = 0;
        for (const int number : nums)
        {
            const int bit1Count = calcBit1Count(number);
            if (currentGroupBit1Count != bit1Count)
            {
                currentGroupBit1Count = bit1Count;
                prevMax = currentMax;
                currentMax = number;
            }
            if (number < prevMax)
                return false;
            currentMax = std::max(currentMax, number);
        }
        return true;
    }

private:
    [[nodiscard]] int calcBit1Count(int number) const
    {
        int bit1Count = 0;
        for (;number > 0; number >>= 1)
        {
            if ((number & 1) > 0)
                ++bit1Count;
        }
        return bit1Count;
    }
};

}

namespace FindIfArrayCanBeSortedTask
{

TEST(FindIfArrayCanBeSortedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canSortArray({8, 4, 2, 30, 15}));
    ASSERT_EQ(true, solution.canSortArray({1, 2, 3, 4, 5}));
    ASSERT_EQ(false, solution.canSortArray({3, 16, 8, 4, 2}));
}

}