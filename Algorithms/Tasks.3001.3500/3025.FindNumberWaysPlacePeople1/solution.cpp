#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfPairs(std::vector<std::vector<int>> const &points) const
    {
        size_t pairsCount = 0;
        for (size_t indexA = 0; indexA < points.size(); ++indexA)
        {
            for (size_t indexB = 0; indexB < points.size(); ++indexB)
            {
                if (indexA == indexB)
                    continue;
                // Alice - upper left corner, Bob - lower right corner
                if ((points[indexA][0] > points[indexB][0]) || (points[indexA][1] < points[indexB][1]))
                    continue;
                pairsCount += (hasPointsInside(points, indexA, indexB) ? 0 : 1);
            }
        }
        return static_cast<int>(pairsCount);
    }

private:
    [[nodiscard]] bool hasPointsInside(std::vector<std::vector<int>> const &points, size_t indexA, size_t indexB) const
    {
        for (size_t index = 0; index < points.size(); ++index)
        {
            if ((index == indexA) || (index == indexB))
                continue;
            if ((points[indexA][0] <= points[index][0]) &&
                (points[index][0] <= points[indexB][0]) &&
                (points[indexB][1] <= points[index][1]) &&
                (points[index][1] <= points[indexA][1]))
                return true;
        }
        return false;
    }
};

}

namespace FindNumberWaysPlacePeople1Task
{

TEST(FindNumberWaysPlacePeople1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numberOfPairs({{1, 1}, {2, 2}, {3, 3}}));
    ASSERT_EQ(2, solution.numberOfPairs({{6, 2}, {4, 4}, {2, 6}}));
    ASSERT_EQ(2, solution.numberOfPairs({{3, 1}, {1, 3}, {1, 1}}));
}

TEST(FindNumberWaysPlacePeople1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numberOfPairs({{0, 0}, {0, 3}}));
}

}