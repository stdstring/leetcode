#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> countPoints(std::vector<std::vector<int>> const &points, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> answers(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            int x0 = queries[index][0];
            int y0 = queries[index][1];
            int radiusSquare = queries[index][2] * queries[index][2];
            auto predicate = [x0, y0, radiusSquare](std::vector<int> const& p) { return (p[0] - x0) * (p[0] - x0) + (p[1] - y0) * (p[1] - y0) <= radiusSquare; };
            answers[index] = static_cast<int>(std::count_if(points.cbegin(), points.cend(), predicate));
        }
        return answers;
    }
};

}

namespace QueriesNumberOfPointsInsideCircleTask
{

TEST(QueriesNumberOfPointsInsideCircleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 2}), solution.countPoints({{1, 3}, {3, 3}, {5, 3}, {2, 2}}, {{2, 3, 1}, {4, 3, 1}, {1, 1, 2}}));
    ASSERT_EQ(std::vector<int>({2, 3, 2, 4}), solution.countPoints({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}, {{1, 2, 2}, {2, 2, 2}, {4, 3, 2}, {4, 3, 3}}));
}

}