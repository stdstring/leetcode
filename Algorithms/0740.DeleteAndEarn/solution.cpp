#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int deleteAndEarn(std::vector<int> const &nums) const
    {
        std::unordered_map<int, int> frequencies;
        int maxNumber = 0;
        for (int number : nums)
        {
            ++frequencies[number];
            maxNumber = std::max(maxNumber, number);
        }
        // maxPoints(0):
        int prevValue = 0;
        // maxPoints(1):
        int currentValue = frequencies.count(1) == 0 ? 0 : frequencies[1];
        for (int number = 2; number <= maxNumber; ++number)
        {
            const int gain = number * (frequencies.count(number) == 0 ? 0 : frequencies[number]);
            const int nextValue = std::max(prevValue + gain, currentValue);
            prevValue = currentValue;
            currentValue = nextValue;
        }
        return currentValue;
    }
};

}

namespace DeleteAndEarnTask
{

TEST(DeleteAndEarnTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.deleteAndEarn({3, 4, 2}));
    ASSERT_EQ(9, solution.deleteAndEarn({2, 2, 3, 3, 3, 4}));
}

TEST(DeleteAndEarnTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(61, solution.deleteAndEarn({8, 3, 4, 7, 6, 6, 9, 2, 5, 8, 2, 4, 9, 5, 9, 1, 5, 7, 1, 4}));
}

}