#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> cycleLengthQueries(int n, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> result;
        for (std::vector<int> const& query : queries)
            result.push_back(calcTotalPathToCommonNode(query[0], query[1]) + 1);
        return result;
    }

private:
    [[nodiscard]] int getParent(int node) const
    {
        return node / 2;
    }

    [[nodiscard]] int calcTotalPathToCommonNode(int node1, int node2) const
    {
        int totalPath = 0;
        while (node1 != node2)
        {
            ++totalPath;
            node1 < node2 ? node2 = getParent(node2) : node1 = getParent(node1);
        }
        return totalPath;
    }
};

}

namespace CycleLengthQueriesInTreeTask
{

TEST(CycleLengthQueriesInTreeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 5, 3}), solution.cycleLengthQueries(3, {{5, 3}, {4, 7}, {2, 3}}));
    ASSERT_EQ(std::vector<int>({2}), solution.cycleLengthQueries(2, {{1, 2}}));
}

}