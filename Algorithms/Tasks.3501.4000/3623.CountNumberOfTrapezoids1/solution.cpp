#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countTrapezoids(std::vector<std::vector<int>> const &points) const
    {
        std::unordered_map<int, size_t> yCoordMap;
        for (std::vector<int> const &point : points)
            ++yCoordMap[point[1]];
        size_t totalPossibleCases = 0;
        std::vector<size_t> possibleCases;
        for (auto const &[_, pointsCount] : yCoordMap)
        {
            if (pointsCount == 1)
                continue;
            possibleCases.emplace_back(calcPossibleCases(pointsCount));
            totalPossibleCases += possibleCases.back();
        }
        if (possibleCases.size() < 2)
            return 0;
        constexpr size_t modValue = 1000000007;
        size_t result = 0;
        for (size_t possibleCasesValue : possibleCases)
        {
            totalPossibleCases -= possibleCasesValue;
            result = (result + possibleCasesValue * totalPossibleCases) % modValue;
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] size_t calcPossibleCases(size_t pointCount) const
    {
        --pointCount;
        if (pointCount < 2)
            return pointCount;
        return (1 + pointCount) * pointCount / 2;
    }
};

}

namespace CountNumberOfTrapezoids1Task
{

TEST(CountNumberOfTrapezoids1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countTrapezoids({{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}}));
    ASSERT_EQ(1, solution.countTrapezoids({{0, 0}, {1, 0}, {0, 1}, {2, 1}}));
}

}