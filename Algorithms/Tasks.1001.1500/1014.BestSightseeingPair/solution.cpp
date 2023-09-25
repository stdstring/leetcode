#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScoreSightseeingPair(std::vector<int> const &values) const
    {
        // values[i] + values[j] + i - j = (values[i] + i) + (values[j] - j)
        int maxValueI = values[0] + 0;
        int bestScore = 0;
        for (size_t index = 1; index < values.size(); ++index)
        {
            const int j = static_cast<int>(index);
            bestScore = std::max(bestScore, maxValueI + (values[j] - j));
            maxValueI = std::max(maxValueI, values[j] + j);
        }
        return bestScore;
    }
};

}

namespace BestSightseeingPairTask
{

TEST(BestSightseeingPairTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.maxScoreSightseeingPair({8, 1, 5, 2, 6}));
    ASSERT_EQ(2, solution.maxScoreSightseeingPair({1, 2}));
}

}