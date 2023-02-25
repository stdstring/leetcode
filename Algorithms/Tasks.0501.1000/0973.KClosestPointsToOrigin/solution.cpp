#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>> const &points, int k) const
    {
        std::vector<std::vector<int>> sortedPoints(points);
        std::sort(sortedPoints.begin(),
                  sortedPoints.end(),
                  [](std::vector<int> const &left, std::vector<int> const &right){ return (left[0] * left[0] + left[1] * left[1]) < (right[0] * right[0] + right[1] * right[1]); });
        std::vector<std::vector<int>> result(sortedPoints.cbegin(), sortedPoints.cbegin() + k);
        return result;
    }
};

}

namespace KClosestPointsToOriginTask
{

TEST(KClosestPointsToOriginTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{-2, 2}}), solution.kClosest({{1, 3}, {-2, 2}}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 3}, {-2, 4}}), solution.kClosest({{3, 3}, {5, -1}, {-2, 4}}, 2));
}

}