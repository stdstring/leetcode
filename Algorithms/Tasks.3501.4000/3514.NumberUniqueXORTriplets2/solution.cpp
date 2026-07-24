#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{
class Solution
{
public:
    [[nodiscard]] int uniqueXorTriplets(std::vector<int> const &nums) const
    {
        const int maxValue = std::ranges::max(nums);
        int maxXorValue = 1;
        while (maxXorValue <= maxValue)
            maxXorValue <<= 1;
        std::vector<bool> firstRound(maxXorValue, false);
        std::vector<bool> secondRound(maxXorValue, false);
        for (const int number : nums)
        {
            firstRound[number] = true;
            for (int value = 0; value < maxXorValue; ++value)
            {
                if (firstRound[value])
                    secondRound[number ^ value] = true;
            }
        }
        std::vector<bool> thirdRound(maxXorValue, false);
        for (const int number : nums)
        {
            for (int value = 0; value < maxXorValue; ++value)
            {
                if (secondRound[value])
                    thirdRound[number ^ value] = true;
            }
        }
        size_t result = 0;
        for (int value = 0; value < maxXorValue; ++value)
        {
            if (thirdRound[value])
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace NumberUniqueXORTriplets2Task
{

TEST(NumberUniqueXORTriplets2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.uniqueXorTriplets({1, 3}));
    ASSERT_EQ(4, solution.uniqueXorTriplets({6, 7, 8, 9}));
}

}