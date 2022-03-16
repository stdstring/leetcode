#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getLastMoment(int n, std::vector<int> const &left, std::vector<int> const &right) const
    {
        const int leftMaxDistance = left.empty() ? 0 : *std::max_element(left.cbegin(), left.cend());
        const int rightMaxDistance = right.empty() ? 0 : n - *std::min_element(right.cbegin(), right.cend());
        return std::max(leftMaxDistance, rightMaxDistance);
    }
};

}

namespace LastMomentBeforeAllAntsFallOutOfPlankTask
{

TEST(LastMomentBeforeAllAntsFallOutOfPlankTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.getLastMoment(4, {4, 3}, {0, 1}));
    ASSERT_EQ(7, solution.getLastMoment(7, {}, {0, 1, 2, 3, 4, 5, 6, 7}));
    ASSERT_EQ(7, solution.getLastMoment(7, {0, 1, 2, 3, 4, 5, 6, 7}, {}));
}

TEST(LastMomentBeforeAllAntsFallOutOfPlankTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.getLastMoment(9, {5}, {4}));
}

}
