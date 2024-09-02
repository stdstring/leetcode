#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> countVisitedNodes(std::vector<int> const &edges) const
    {
        const int nodeCount = static_cast<int>(edges.size());
        std::vector<int> result(nodeCount, 0);
        for (int node = 0; node < nodeCount; ++node)
        {
            if (result[node] == 0)
                visitNode(edges, result, node);
        }
        return result;
    }

private:
    void visitNode(std::vector<int> const &edges, std::vector<int> &result, int start) const
    {
        std::vector<int> path;
        int node = start;
        int visitedCount = -1;
        for(;result[node] == 0; node = edges[node])
        {
            result[node] = visitedCount;
            path.emplace_back(node);
            --visitedCount;
        }
        if (result[node] > 0)
        {
            int shift = 1;
            for (auto iterator = path.rbegin(); iterator != path.rend(); ++iterator)
            {
                result[*iterator] = result[node] + shift;
                ++shift;
            }
        }
        else
        {
            int shift = std::abs(result[path.back()] - result[node]) + 1;
            int delta = 0;
            for (auto iterator = path.rbegin(); iterator != path.rend(); ++iterator)
            {
                result[*iterator] = shift;
                if (*iterator == node)
                    delta = 1;
                shift += delta;
            }
        }
    }
};

}

namespace CountVisitedNodesInDirectedGraphTask
{

TEST(CountVisitedNodesInDirectedGraphTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 3, 3, 4}), solution.countVisitedNodes({1, 2, 0, 0}));
    ASSERT_EQ(std::vector<int>({5, 5, 5, 5, 5}), solution.countVisitedNodes({1, 2, 3, 4, 0}));
}

}