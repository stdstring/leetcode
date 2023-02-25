#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> intervalIntersection(std::vector<std::vector<int>> const &firstList, std::vector<std::vector<int>> const &secondList) const
    {
        std::vector<std::vector<int>> result;
        size_t firstIndex = 0;
        size_t secondIndex = 0;
        while (firstIndex < firstList.size() && secondIndex < secondList.size())
        {
            std::vector<int> const &firstInterval = firstList[firstIndex];
            std::vector<int> const &secondInterval = secondList[secondIndex];
            if ((secondInterval[0] <= firstInterval[0] && firstInterval[0] <= secondInterval[1]) ||
                (firstInterval[0] <= secondInterval[0] && secondInterval[0] <= firstInterval[1]))
                result.push_back(std::vector<int>({std::max(firstInterval[0], secondInterval[0]), std::min(firstInterval[1], secondInterval[1])}));
            if (firstInterval[1] <= secondInterval[1])
                ++firstIndex;
            if (firstInterval[1] >= secondInterval[1])
                ++secondIndex;
        }
        return result;
    }
};

}

namespace IntervalListIntersectionsTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}}),
              solution.intervalIntersection({{0, 2}, {5, 10}, {13, 23}, {24, 25}}, {{1, 5}, {8, 12}, {15, 24}, {25, 26}}));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.intervalIntersection({{1, 3}, {5, 9}}, {}));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.intervalIntersection({}, {{4, 8}, {10, 12}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 7}}), solution.intervalIntersection({{1, 7}}, {{3, 10}}));
}

}