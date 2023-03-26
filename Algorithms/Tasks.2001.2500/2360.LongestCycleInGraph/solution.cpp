#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestCycle(std::vector<int> const &edges) const
    {
        int bestCycle = -1;
        std::vector<bool> visited(edges.size(), false);
        for (size_t node = 0; node < edges.size(); ++node)
        {
            if (!visited[node])
                bestCycle = std::max(bestCycle, processPath(static_cast<int>(node), edges, visited));
        }
        return bestCycle;
    }

private:
    [[nodiscard]] int processPath(int node, std::vector<int> const &edges, std::vector<bool> &visited) const
    {
        std::unordered_map<int, int> visitedNodesMap;
        int step = 0;
        while ((node != -1) && !visited[node])
        {
            visited[node] = true;
            visitedNodesMap.emplace(node, step);
            ++step;
            node = edges[node];
        }
        const auto iterator = visitedNodesMap.find(node);
        return iterator == visitedNodesMap.cend() ? -1 : step - iterator->second;
    }
};

}

namespace LongestCycleInGraphTask
{

TEST(LongestCycleInGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestCycle({3, 3, 4, 2, 3}));
    ASSERT_EQ(-1, solution.longestCycle({2, -1, 3, 1}));
}

}