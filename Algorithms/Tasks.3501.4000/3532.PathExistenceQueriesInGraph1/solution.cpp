#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> pathExistenceQueries(int n, std::vector<int> const &nums, int maxDiff, std::vector<std::vector<int>> const &queries) const
    {
        const size_t nodesCount = n;
        std::vector<int> components(n, 0);
        int componentNumber = 0;
        for (size_t current = 0, end = 0; (current < nodesCount) && (end < nodesCount); ++current)
        {
            if (components[current] == 0)
                ++componentNumber;
            for (; (end < nodesCount) && ((nums[end] - nums[current]) <= maxDiff); ++end)
                components[end] = componentNumber;
        }
        std::vector<bool> result(queries.size(), false);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const int node1 = queries[index][0];
            const int node2 = queries[index][1];
            result[index] = (components[node1] == components[node2]);
        }
        return result;
    }
};

}

namespace PathExistenceQueriesInGraph1Task
{

TEST(PathExistenceQueriesInGraph1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({true, false}),
              solution.pathExistenceQueries(2, {1, 3}, 1, {{0, 0}, {0, 1}}));
    ASSERT_EQ(std::vector<bool>({false, false, true, true}),
              solution.pathExistenceQueries(4, {2, 5, 6, 8}, 2, {{0, 1}, {0, 2}, {1, 3}, {2, 3}}));
}

}
