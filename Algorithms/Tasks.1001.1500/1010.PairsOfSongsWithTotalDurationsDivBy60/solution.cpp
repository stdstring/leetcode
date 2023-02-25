#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numPairsDivisibleBy60(std::vector<int> const &time) const
    {
        constexpr int dividerValue = 60;
        constexpr int maxValue = 500;
        std::vector<size_t> valuesCount(maxValue + 1);
        for (const int value : time)
            ++valuesCount[value];
        size_t totalPairsCount = 0;
        for (int value = 1; value <= maxValue; ++value)
        {
            int dividend = dividerValue;
            while ((dividend - value) <= maxValue)
            {
                const int otherValue = dividend - value;
                if (otherValue > value)
                    totalPairsCount += (valuesCount[value] * valuesCount[otherValue]);
                if (otherValue == value)
                    totalPairsCount += ((valuesCount[value] - 1) * valuesCount[value] / 2);
                dividend += dividerValue;
            }
        }
        return static_cast<int>(totalPairsCount);
    }
};

}

namespace PairsOfSongsWithTotalDurationsDivBy60Task
{

TEST(PairsOfSongsWithTotalDurationsDivBy60TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numPairsDivisibleBy60({30, 20, 150, 100, 40}));
    ASSERT_EQ(3, solution.numPairsDivisibleBy60({60, 60, 60}));
}

TEST(PairsOfSongsWithTotalDurationsDivBy60TaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.numPairsDivisibleBy60({439, 407, 197, 191, 291, 486, 30, 307, 11}));
}

}