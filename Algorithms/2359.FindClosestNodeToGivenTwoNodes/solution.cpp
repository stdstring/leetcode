#include <optional>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"


namespace
{

class Solution
{
public:
    [[nodiscard]] int closestMeetingNode(std::vector<int> const &edges, int node1, int node2) const
    {
        const std::vector<int> node1Path(calcPath(edges, node1));
        const std::vector<int> node2Path(calcPath(edges, node2));
        std::optional<int> bestValue;
        int bestNode = -1;
        for (int node = 0; node < static_cast<int>(edges.size()); ++node)
        {
            if ((node1Path[node] == -1) || (node2Path[node] == -1))
                continue;
            int currentValue = std::max(node1Path[node], node2Path[node]);
            if (!bestValue.has_value() || (currentValue <= bestValue.value()))
            {
                if (bestValue.has_value() && (currentValue == bestValue.value()))
                    bestNode = bestNode == -1 ? node : std::min(bestNode, node);
                else
                    bestNode = node;
                bestValue = currentValue;
            }
        }
        return bestNode;
    }

private:
    [[nodiscard]] std::vector<int> calcPath(std::vector<int> const &edges, int node) const
    {
        std::unordered_set<int> visited;
        std::vector<int> nodePath(edges.size(), -1);
        int length = 0;
        while (node != -1)
        {
            if (visited.count(node) != 0)
                break;
            nodePath[node] = length;
            ++length;
            visited.insert(node);
            node = edges[node];
        }
        return nodePath;
    }
};

}

namespace FindClosestNodeToGivenTwoNodesTask
{

TEST(FindClosestNodeToGivenTwoNodesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.closestMeetingNode({2, 2, 3, -1}, 0, 1));
    ASSERT_EQ(2, solution.closestMeetingNode({1, 2, -1}, 0, 2));
}

TEST(FindClosestNodeToGivenTwoNodesTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.closestMeetingNode({5, 3, 1, 0, 2, 4, 5}, 3, 2));
    ASSERT_EQ(7, solution.closestMeetingNode({-1, 7, 15, 15, -1, 4, 16, 2, 16, 7, 11, 6, 10, 4, 9, 1, 14, -1}, 1, 6));
    ASSERT_EQ(-1, solution.closestMeetingNode({5, 4, 5, 4, 3, 6, -1}, 0, 1));
    ASSERT_EQ(1, solution.closestMeetingNode({4, 4, 8, -1, 9, 8, 4, 4, 1, 1}, 5, 6));
}

}