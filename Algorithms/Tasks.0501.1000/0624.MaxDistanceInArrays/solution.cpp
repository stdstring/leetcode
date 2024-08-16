#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::vector<std::vector<int>> const &arrays) const
    {
        std::pair<int, size_t> maxFirst(INT_MIN, arrays.size());
        std::pair<int, size_t> maxSecond(INT_MIN, arrays.size());
        for (size_t index = 0; index < arrays.size(); ++index)
        {
            if (arrays[index].back() >= maxFirst.first)
            {
                maxSecond = maxFirst;
                maxFirst = std::pair<int, size_t>(arrays[index].back(), index);
            }
            else if ((arrays[index].back() > maxSecond.first) && (arrays[index].back() < maxFirst.first))
                maxSecond = std::pair<int, size_t>(arrays[index].back(), index);
        }
        int maxDistance = 0;
        for (size_t index = 0; index < arrays.size(); ++index)
            maxDistance = std::max(maxDistance, (index == maxFirst.second ? maxSecond.first : maxFirst.first) - arrays[index].front());
        return maxDistance;
    }
};

}

namespace MaxDistanceInArraysTask
{

TEST(MaxDistanceInArraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxDistance({{1, 2, 3}, {4, 5}, {1, 2, 3}}));
    ASSERT_EQ(0, solution.maxDistance({{1}, {1}}));
}

TEST(MaxDistanceInArraysTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.maxDistance({{1, 10}, {2, 3}}));
}

TEST(MaxDistanceInArraysTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxDistance({{-2}, {-3, -2, 1}}));
}

}