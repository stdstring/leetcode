#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findCenter(std::vector<std::vector<int>> const &edges) const
    {
        const int n1 = edges[0][0];
        const int n2 = edges[0][1];
        const int n3 = edges[1][0];
        const int n4 = edges[1][1];
        if ((n1 == n2) || (n1 == n3) || (n1 == n4))
            return n1;
        if ((n2 == n3) || (n2 == n4))
            return n2;
        return n3;
    }
};

}

namespace FindCenterOfStarGraphTask
{

TEST(FindCenterOfStarGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findCenter({{1, 2}, {2, 3}, {4, 2}}));
    ASSERT_EQ(1, solution.findCenter({{1, 2}, {5, 1}, {1, 3}, {1, 4}}));
}

}