#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfArrays(std::vector<int> const &differences, int lower, int upper) const
    {
        long long currentShift = 0;
        long long minShift = differences.front() > 0 ? 0 : differences.front();
        long long maxShift = differences.front() < 0 ? 0 : differences.front();
        for (const int difference : differences)
        {
            currentShift += difference;
            minShift = std::min(minShift, currentShift);
            maxShift = std::max(maxShift, currentShift);
        }
        const long long shiftDelta = maxShift - minShift + 1;
        const long long rangeDelta = upper - lower + 1;
        if (rangeDelta < shiftDelta)
            return 0;
        return static_cast<int>(rangeDelta - shiftDelta + 1);
    }
};

}

namespace CountHiddenSequencesTask
{

TEST(CountHiddenSequencesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numberOfArrays({1, -3, 4}, 1, 6));
    ASSERT_EQ(4, solution.numberOfArrays({3, -4, 5, 1, -2}, -4, 5));
    ASSERT_EQ(0, solution.numberOfArrays({4, -7, 2}, 3, 6));
}

TEST(CountHiddenSequencesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(60, solution.numberOfArrays({-40}, -46, 53));
}

}